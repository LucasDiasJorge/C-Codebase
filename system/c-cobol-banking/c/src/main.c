#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ACCOUNTS 128
#define MAX_LINE 256

#define ACCOUNTS_FILE "data/accounts.csv"
#define REQUEST_FILE "runtime/request.txt"
#define RESPONSE_FILE "runtime/response.txt"
#define COBOL_ENGINE "./bin/cobol_engine"

typedef struct {
    char id[7];
    char name[64];
    double balance;
} Account;

typedef struct {
    char status[16];
    double new_balance;
    char code[32];
    char message[128];
} EngineResponse;

static int load_accounts(Account *accounts, size_t *count) {
    FILE *file = fopen(ACCOUNTS_FILE, "r");
    char line[MAX_LINE];

    if (file == NULL) {
        fprintf(stderr, "Erro ao abrir %s: %s\n", ACCOUNTS_FILE, strerror(errno));
        return -1;
    }

    *count = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        char *id = NULL;
        char *name = NULL;
        char *balance = NULL;

        line[strcspn(line, "\r\n")] = '\0';
        id = strtok(line, "|");
        name = strtok(NULL, "|");
        balance = strtok(NULL, "|");

        if (id == NULL || name == NULL || balance == NULL) {
            continue;
        }

        if (*count >= MAX_ACCOUNTS) {
            fprintf(stderr, "Limite de contas atingido (%d).\n", MAX_ACCOUNTS);
            fclose(file);
            return -1;
        }

        strncpy(accounts[*count].id, id, sizeof(accounts[*count].id) - 1);
        accounts[*count].id[sizeof(accounts[*count].id) - 1] = '\0';

        strncpy(accounts[*count].name, name, sizeof(accounts[*count].name) - 1);
        accounts[*count].name[sizeof(accounts[*count].name) - 1] = '\0';

        accounts[*count].balance = strtod(balance, NULL);
        (*count)++;
    }

    fclose(file);
    return 0;
}

static int save_accounts(const Account *accounts, size_t count) {
    FILE *file = fopen(ACCOUNTS_FILE, "w");
    size_t i = 0;

    if (file == NULL) {
        fprintf(stderr, "Erro ao salvar %s: %s\n", ACCOUNTS_FILE, strerror(errno));
        return -1;
    }

    for (i = 0; i < count; i++) {
        fprintf(file, "%s|%s|%.2f\n", accounts[i].id, accounts[i].name, accounts[i].balance);
    }

    fclose(file);
    return 0;
}

static int find_account_index(const Account *accounts, size_t count, const char *id) {
    size_t i = 0;
    for (i = 0; i < count; i++) {
        if (strcmp(accounts[i].id, id) == 0) {
            return (int)i;
        }
    }
    return -1;
}

static int write_request(const char *operation, const Account *account, double amount) {
    FILE *file = fopen(REQUEST_FILE, "w");

    if (file == NULL) {
        fprintf(stderr, "Erro ao criar %s: %s\n", REQUEST_FILE, strerror(errno));
        return -1;
    }

    fprintf(file, "%s|%s|%.2f|%.2f\n", operation, account->id, account->balance, amount);
    fclose(file);
    return 0;
}

static int run_cobol_engine(void) {
    int rc = system(COBOL_ENGINE);
    if (rc != 0) {
        fprintf(stderr, "Falha ao executar o core COBOL (codigo %d).\n", rc);
        return -1;
    }
    return 0;
}

static int read_response(EngineResponse *response) {
    FILE *file = fopen(RESPONSE_FILE, "r");
    char line[MAX_LINE];
    char *status = NULL;
    char *new_balance = NULL;
    char *code = NULL;
    char *message = NULL;

    if (file == NULL) {
        fprintf(stderr, "Erro ao ler %s: %s\n", RESPONSE_FILE, strerror(errno));
        return -1;
    }

    if (fgets(line, sizeof(line), file) == NULL) {
        fclose(file);
        fprintf(stderr, "Resposta COBOL vazia.\n");
        return -1;
    }

    fclose(file);

    line[strcspn(line, "\r\n")] = '\0';
    status = strtok(line, "|");
    new_balance = strtok(NULL, "|");
    code = strtok(NULL, "|");
    message = strtok(NULL, "");

    if (status == NULL || new_balance == NULL || code == NULL || message == NULL) {
        fprintf(stderr, "Formato de resposta invalido do COBOL.\n");
        return -1;
    }

    strncpy(response->status, status, sizeof(response->status) - 1);
    response->status[sizeof(response->status) - 1] = '\0';

    response->new_balance = strtod(new_balance, NULL);

    strncpy(response->code, code, sizeof(response->code) - 1);
    response->code[sizeof(response->code) - 1] = '\0';

    strncpy(response->message, message, sizeof(response->message) - 1);
    response->message[sizeof(response->message) - 1] = '\0';

    return 0;
}

static int process_transaction(const char *operation, const char *account_id, double amount) {
    Account accounts[MAX_ACCOUNTS];
    size_t count = 0;
    int idx = -1;
    EngineResponse response;

    if (load_accounts(accounts, &count) != 0) {
        return -1;
    }

    idx = find_account_index(accounts, count, account_id);
    if (idx < 0) {
        fprintf(stderr, "Conta %s nao encontrada.\n", account_id);
        return -1;
    }

    if (write_request(operation, &accounts[idx], amount) != 0) {
        return -1;
    }

    if (run_cobol_engine() != 0) {
        return -1;
    }

    if (read_response(&response) != 0) {
        return -1;
    }

    printf("[CORE COBOL] status=%s code=%s message=%s\n", response.status, response.code, response.message);

    if (strcmp(response.status, "APPROVED") == 0) {
        accounts[idx].balance = response.new_balance;
        if (save_accounts(accounts, count) != 0) {
            return -1;
        }
    }

    printf("Conta %s (%s) | Saldo atual: %.2f\n\n", accounts[idx].id, accounts[idx].name, accounts[idx].balance);
    return 0;
}

int main(void) {
    printf("=== Integracao C + COBOL: Gateway Bancario ===\n\n");

    if (process_transaction("DEPOSIT", "000001", 250.00) != 0) {
        return EXIT_FAILURE;
    }

    if (process_transaction("WITHDRAW", "000002", 100.00) != 0) {
        return EXIT_FAILURE;
    }

    if (process_transaction("WITHDRAW", "000002", 1000.00) != 0) {
        return EXIT_FAILURE;
    }

    if (process_transaction("WITHDRAW", "000003", -10.00) != 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

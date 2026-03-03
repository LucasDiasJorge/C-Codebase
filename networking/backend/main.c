#include <microhttpd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define PORT 8080

// Function to handle the "/hello" route
int hello_handler(void *cls, struct MHD_Connection *connection,
                  const char *url, const char *method,
                  const char *version, const char *upload_data,
                  size_t *upload_data_size, void **con_cls) {
    const char *token = MHD_lookup_connection_value(connection, MHD_HEADER_KIND, "Authorization");

    // Check if the Authorization header is present and has a valid Bearer token
    if (token != NULL && strncmp(token, "Bearer ", 7) == 0) {
        // Extract the token value (ignoring "Bearer ")
        const char *tokenValue = token + 7;

        // TODO: Add your logic to validate the bearer token

        // Respond with a JSON containing "hello"
        const char *response = "{\"message\": \"hello\"}";
        struct MHD_Response *json_response = MHD_create_response_from_buffer(strlen(response), (void *)response, MHD_RESPMEM_MUST_COPY);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, json_response);
        MHD_destroy_response(json_response);

        return ret;
    } else {
        // Unauthorized access without a valid Bearer token
        const char *response = "{\"error\": \"Unauthorized\"}";
        struct MHD_Response *json_response = MHD_create_response_from_buffer(strlen(response), (void *)response, MHD_RESPMEM_MUST_COPY);
        int ret = MHD_queue_response(connection, MHD_HTTP_UNAUTHORIZED, json_response);
        MHD_destroy_response(json_response);

        return ret;
    }
}

bool debug = false;

void debugging(char *message) {
    if (debug) {
        printf("\tLog: %s;\n", message);
    }
}

void init() {
    if (debug) {
        printf("File: %s\n", __FILE__);
        printf("Date: %s\n", __DATE__);
        printf("Time: %s\n", __TIME__);
        printf("Line: %d\n", __LINE__);
        printf("ANSI: %d\n", __STDC__);
    }
}

int main(int argc, char *argv[]) {

    if (argc >= 2 && strcmp("--debug", argv[1]) == 0) {
        debug = true;
    }

    init();

    debugging("Instancing struct MHD_Daemon as *daemon");

    struct MHD_Daemon *daemon;

    debugging("Starting daemon in PORT: 8080, using \"hello_handler\" function");

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &hello_handler, NULL, MHD_OPTION_END);

    if (NULL == daemon) {
        return 1;
    }

    debugging("Press \"Enter\" to stop the server");

    getchar(); // Press Enter to stop the server

    debugging("Stopping server");

    MHD_stop_daemon(daemon);

    debugging("Exiting");

    return 0;
}

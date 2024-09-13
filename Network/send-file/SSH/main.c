#include <stdlib.h>
#include <stdio.h>
#define LIBSSH_STATIC 1
#include <libssh/libssh.h>
#include <libssh/sftp.h>
#include <sys/stat.h>


int main(void){
    int rc;
    int port = 22;
    char *pass = "pass";

    // Create a new SSH session
    ssh_session my_ssh_session = ssh_new();
    if(my_ssh_session == NULL){
        exit(-1);
    }

    // Set SSH options: host IP, port, and user
    ssh_options_set(my_ssh_session, SSH_OPTIONS_HOST, "ip");
    ssh_options_set(my_ssh_session, SSH_OPTIONS_PORT, &port);
    ssh_options_set(my_ssh_session, SSH_OPTIONS_USER, "user");

    // Connect to the SSH server
    rc = ssh_connect(my_ssh_session);
    if(rc != SSH_OK){
        fprintf(stderr, "Error connecting to localhost: %s\n", ssh_get_error(my_ssh_session) );
        exit(-1);
    } 

    // Authenticate with password
    rc = ssh_userauth_password(my_ssh_session, NULL, pass);
    if(rc != SSH_AUTH_SUCCESS){
        fprintf(stderr, "Authentication failed: %s\n", ssh_get_error(my_ssh_session));
        ssh_disconnect(my_ssh_session);
        ssh_free(my_ssh_session);
        exit(-1);
    }

    // Start SCP session to send a file
    ssh_scp scp = ssh_scp_new(my_ssh_session, SSH_SCP_WRITE, "/home/user");
    if(scp == NULL){
        fprintf(stderr, "Error allocating SCP session: %s\n", ssh_get_error(my_ssh_session));
        exit(-1);
    }

    // Initialize the SCP session
    rc = ssh_scp_init(scp);
    if(rc != SSH_OK){
        fprintf(stderr, "Error initializing SCP session: %s\n", ssh_get_error(my_ssh_session));
        ssh_scp_free(scp);
        exit(-1);
    }

    // Push the file to the remote server
    rc = ssh_scp_push_file(scp, "response.json", 1024, S_IRUSR | S_IWUSR);
    if(rc != SSH_OK){
        fprintf(stderr, "Error pushing file: %s\n", ssh_get_error(my_ssh_session));
        ssh_scp_close(scp);
        ssh_scp_free(scp);
        exit(-1);
    }

    // Open the local file to transfer
    FILE *file = fopen("response.json", "rb");
    if(file == NULL){
        fprintf(stderr, "Error opening local file: response.json\n");
        ssh_scp_close(scp);
        ssh_scp_free(scp);
        exit(-1);
    }

    // Read file data and write it to the SCP session
    char buffer[1024];
    size_t nread;
    while((nread = fread(buffer, 1, sizeof(buffer), file)) > 0){
        rc = ssh_scp_write(scp, buffer, nread);
        if(rc != SSH_OK){
            fprintf(stderr, "Error writing to SCP session: %s\n", ssh_get_error(my_ssh_session));
            fclose(file);
            ssh_scp_close(scp);
            ssh_scp_free(scp);
            exit(-1);
        }
    }

    // Close the file and SCP session
    fclose(file);
    ssh_scp_close(scp);
    ssh_scp_free(scp);

    // Disconnect from the SSH session and free memory
    ssh_disconnect(my_ssh_session);
    ssh_free(my_ssh_session);

    return 0;
}

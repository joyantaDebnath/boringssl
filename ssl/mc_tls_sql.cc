// #include "mc_tls_sql.h"
// #include<iostream>
// // #include<mysql/mysql.h>
// // #include "internal.h"

// // bool add_new_state(struct TLS13state state, int state_counter, char state_hash[]) {
// //     MYSQL *mysql = NULL;

// //     const char* host = "localhost";
// //     const char* user = "joy";
// //     const char* passwd = "@Joyanta1234";
// //     const char* db = "mydatabase";
// //     char server_name[] = "boringssl";

// //     const char* insert_query = "insert into mc_tls_state_info (server_name, state_counter, session_id_set, random_set, handshake_secret_set, handshake_key_set, handshake_iv_set, master_secret_set, application_key_set, application_iv_set, error_status_set, terminated_set, message_expected, message_received, message_sent, state_hash) values(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);";

// //     mysql = mysql_init(NULL);
// //     if(mysql == NULL){
// //       fprintf(stderr, "failed to initialise mysql");
// //     }

// //     if (mysql_real_connect(mysql, host, user, passwd, db, 0, NULL, 0) == NULL) {
// //         fprintf(stderr, "ERROR:mysql_real_connect() failed.\n");
// //         exit(1);
// //     }

// //     MYSQL_STMT *statement = NULL;
// //     statement = mysql_stmt_init(mysql);
// //     if(statement==NULL){
// //         fprintf(stderr, "failed to initalise sql prepared statement");
// //         exit(1);
// //     }

// //     int ret = mysql_stmt_prepare(statement, insert_query, strlen(insert_query));
// //     if (ret){
// //         fprintf(stderr, "failed to prepare statement due to %d", ret);
// //         fprintf(stderr, "%s" , mysql_stmt_error(statement));
// //         exit(1);
// //     }

// //     MYSQL_BIND input_bind[16];

// //     memset(input_bind, 0, sizeof(input_bind));
    
// //     int i = 0;
// //     unsigned long long_len = sizeof(state_counter);
// //     unsigned long bool_len = sizeof(state.session_id_set);
// //     unsigned long server_name_len = sizeof(server_name);
// //     unsigned long msg_expected_len = sizeof(state.message_expected);
// //     unsigned long msg_received_len = sizeof(state.message_received);
// //     unsigned long msg_sent_len = sizeof(state.message_sent);
// //     unsigned long state_hash_len = 65;

// //     input_bind[i].buffer_type = MYSQL_TYPE_STRING;
// //     input_bind[i].buffer = server_name;
// //     input_bind[i].buffer_length = sizeof(server_name);
// //     input_bind[i++].length = &server_name_len;

// //     input_bind[i].buffer_type = MYSQL_TYPE_LONG;
// //     input_bind[i].buffer = &state_counter;
// //     input_bind[i].buffer_length = sizeof(state_counter);
// //     input_bind[i++].length = &long_len;

// //     input_bind[i].buffer_type = MYSQL_TYPE_TINY;
// //     input_bind[i].buffer = &state.session_id_set;
// //     input_bind[i].buffer_length = sizeof(state.session_id_set);
// //     input_bind[i++].length = &bool_len;
    
// //     input_bind[i].buffer_type = MYSQL_TYPE_TINY;
// //     input_bind[i].buffer = &state.random_set;
// //     input_bind[i].buffer_length = sizeof(state.random_set);
// //     input_bind[i++].length = &bool_len;
    
// //     input_bind[i].buffer_type = MYSQL_TYPE_TINY;
// //     input_bind[i].buffer = &state.handshake_secret_set;
// //     input_bind[i].buffer_length = sizeof(state.handshake_secret_set);
// //     input_bind[i++].length = &bool_len;
    
// //     input_bind[i].buffer_type = MYSQL_TYPE_TINY;
// //     input_bind[i].buffer = &state.handshake_key_set;
// //     input_bind[i].buffer_length = sizeof(state.handshake_key_set);
// //     input_bind[i++].length = &bool_len;
    
// //     input_bind[i].buffer_type = MYSQL_TYPE_TINY;
// //     input_bind[i].buffer = &state.handshake_iv_set;
// //     input_bind[i].buffer_length = sizeof(state.handshake_iv_set);
// //     input_bind[i++].length = &bool_len;
    
// //     input_bind[i].buffer_type = MYSQL_TYPE_TINY;
// //     input_bind[i].buffer = &state.master_secret_set;
// //     input_bind[i].buffer_length = sizeof(state.master_secret_set);
// //     input_bind[i++].length = &bool_len;
    
// //     input_bind[i].buffer_type = MYSQL_TYPE_TINY;
// //     input_bind[i].buffer = &state.application_key_set;
// //     input_bind[i].buffer_length = sizeof(state.application_key_set);
// //     input_bind[i++].length = &bool_len;
    
// //     input_bind[i].buffer_type = MYSQL_TYPE_TINY;
// //     input_bind[i].buffer = &state.application_iv_set;
// //     input_bind[i].buffer_length = sizeof(state.application_iv_set);
// //     input_bind[i++].length = &bool_len;
    
// //     input_bind[i].buffer_type = MYSQL_TYPE_TINY;
// //     input_bind[i].buffer = &state.error_status;
// //     input_bind[i].buffer_length = sizeof(state.error_status);
// //     input_bind[i++].length = &bool_len;

// //     input_bind[i].buffer_type = MYSQL_TYPE_TINY;
// //     input_bind[i].buffer = &state.terminated;
// //     input_bind[i].buffer_length = sizeof(state.terminated);
// //     input_bind[i++].length = &bool_len;

// //     input_bind[i].buffer_type = MYSQL_TYPE_STRING;
// //     input_bind[i].buffer = state.message_expected;
// //     input_bind[i].buffer_length = sizeof(state.message_expected);
// //     input_bind[i++].length = &msg_expected_len;    

// //     input_bind[i].buffer_type = MYSQL_TYPE_STRING;
// //     input_bind[i].buffer = state.message_received;
// //     input_bind[i].buffer_length = sizeof(state.message_received);
// //     input_bind[i++].length = &msg_received_len; 

// //     input_bind[i].buffer_type = MYSQL_TYPE_STRING;
// //     input_bind[i].buffer = state.message_sent;
// //     input_bind[i].buffer_length = sizeof(state.message_sent);
// //     input_bind[i++].length = &msg_sent_len;

// //     input_bind[i].buffer_type = MYSQL_TYPE_STRING;
// //     input_bind[i].buffer = (char*)state_hash;
// //     input_bind[i].buffer_length = 65;
// //     input_bind[i++].length = &state_hash_len;  

// //     if (mysql_stmt_bind_param(statement, input_bind)) {
// //         fprintf(stderr, "ERROR:mysql_stmt_bind_param failed\n");
// //         exit(1);
// //     }

// //     if (mysql_stmt_execute(statement)) {
// //         fprintf(stderr, "mysql_stmt_execute(), failed. Error:%s\n", mysql_stmt_error(statement));
// //         exit(1);
// //     }

// //     return true;
// // }

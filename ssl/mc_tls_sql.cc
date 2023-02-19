#include "mc_tls_sql.h"
#include<iostream>
#include<mysql/mysql.h>
// #include "internal.h"

bool add_new_state(  TLS13state  state, int state_counter){
    MYSQL *mysql =NULL;

    const char* host = "localhost";
    const char* user = "root";
    const char* passwd = "password";
    const char* db = "mydatabase";

    // const char* insert_query = "insert into mc_tls_state_info (state_counter, test_server_id, session_id_set , random_set,handshake_secret_set, handshake_key_set,handshake_iv_set,master_secret_set,application_key_set,application_iv_set, error_status_set, message_received, message_sent  ) values(?,?,?,?,?,?,?,?,?,?,?,?,? ); ";
    const char* insert_query = "insert into mc_tls_state_info (state_counter, test_server_id, session_id_set , random_set,handshake_secret_set, handshake_key_set,handshake_iv_set,master_secret_set,application_key_set,application_iv_set, error_status_set, is_terminated  ) values(?,?,?,?,?,?,?,?,?,?,?,?); ";

    mysql =mysql_init(NULL);
    if(mysql == NULL){
      fprintf(stderr, "failed to initialise mysql");
    }
    else{
      fprintf(stdout, "initialised mysql1\n"); 
    }
      if (mysql_real_connect(mysql, host, user, passwd, db, 0, NULL, 0) == NULL) {
        fprintf(stderr, "ERROR:mysql_real_connect() failed.\n");
        exit(1);
    }


    MYSQL_STMT *statement = NULL;
    statement = mysql_stmt_init(mysql);
    if(statement==NULL){
        fprintf(stderr,"failed to initalise sql prepared statement");
        exit(1);
    }
    int ret = mysql_stmt_prepare(statement,insert_query, strlen(insert_query));
    if (ret){
        fprintf (stderr,"failed to prepare statement due to %d", ret);
        fprintf (stderr,"%s" ,mysql_stmt_error(statement));
        exit(1);
    }
    MYSQL_BIND input_bind[13];

    memset (input_bind,0,sizeof(input_bind));

    unsigned long id_len = sizeof(state_counter);
    unsigned long bool_len = sizeof(state.session_id_set);
    // unsigned long msg_rx_len = sizeof(state->message_received);
    
    int i =0; 

    input_bind[i].buffer_type = MYSQL_TYPE_LONG;
    input_bind[i].buffer = &state_counter;
    input_bind[i].buffer_length = sizeof(state_counter);
    input_bind[i++].length = &id_len;

    input_bind[i].buffer_type = MYSQL_TYPE_LONG;
    input_bind[i].buffer = &state.test_server_id;
    input_bind[i].buffer_length = sizeof(state.test_server_id);
    input_bind[i++].length = &id_len;

    input_bind[i].buffer_type = MYSQL_TYPE_TINY;
    input_bind[i].buffer = &state.session_id_set;
    input_bind[i].buffer_length = sizeof(state.session_id_set);
    input_bind[i++].length = &bool_len;
    
    input_bind[i].buffer_type = MYSQL_TYPE_TINY;
    input_bind[i].buffer = &state.random_set;
    input_bind[i].buffer_length = sizeof(state.random_set);
    input_bind[i++].length = &bool_len;
    
    input_bind[i].buffer_type = MYSQL_TYPE_TINY;
    input_bind[i].buffer = &state.handshake_secret_set;
    input_bind[i].buffer_length = sizeof(state.handshake_secret_set);
    input_bind[i++].length = &bool_len;
    
    input_bind[i].buffer_type = MYSQL_TYPE_TINY;
    input_bind[i].buffer = &state.handshake_key_set;
    input_bind[i].buffer_length = sizeof(state.handshake_key_set);
    input_bind[i++].length = &bool_len;
    
    input_bind[i].buffer_type = MYSQL_TYPE_TINY;
    input_bind[i].buffer = &state.handshake_iv_set;
    input_bind[i].buffer_length = sizeof(state.handshake_iv_set);
    input_bind[i++].length = &bool_len;
    
    input_bind[i].buffer_type = MYSQL_TYPE_TINY;
    input_bind[i].buffer = &state.master_secret_set;
    input_bind[i].buffer_length = sizeof(state.master_secret_set);
    input_bind[i++].length = &bool_len;
    
    input_bind[i].buffer_type = MYSQL_TYPE_TINY;
    input_bind[i].buffer = &state.application_key_set;
    input_bind[i].buffer_length = sizeof(state.application_key_set);
    input_bind[i++].length = &bool_len;
    
    input_bind[i].buffer_type = MYSQL_TYPE_TINY;
    input_bind[i].buffer = &state.application_iv_set;
    input_bind[i].buffer_length = sizeof(state.application_iv_set);
    input_bind[i++].length = &bool_len;
    
    input_bind[i].buffer_type = MYSQL_TYPE_TINY;
    input_bind[i].buffer = &state.error_status;
    input_bind[i].buffer_length = sizeof(state.error_status);
    input_bind[i++].length = &bool_len;
    
    input_bind[i].buffer_type = MYSQL_TYPE_TINY;
    input_bind[i].buffer = &state.terminated;
    input_bind[i].buffer_length = sizeof(state.terminated);
    input_bind[i++].length = &bool_len;

    // input_bind[i].buffer_type = MYSQL_TYPE_TINY;
    // input_bind[i].buffer = &state->message_received;
    // input_bind[i].buffer_length = sizeof(state->message_received);
    // input_bind[i++].length = &msg_rx_len;    

    // input_bind[i].buffer_type = MYSQL_TYPE_TINY;
    // input_bind[i].buffer = &state->message_received;
    // input_bind[i].buffer_length = sizeof(state->message_received);
    // input_bind[i++].length = &msg_rx_len;
    


    if (mysql_stmt_bind_param(statement, input_bind)) {
        fprintf(stderr, "ERROR:mysql_stmt_bind_param failed\n");
        exit(1);
    }

    if (mysql_stmt_execute(statement)) {
        fprintf(stderr, "mysql_stmt_execute(), failed. Error:%s\n", mysql_stmt_error(statement));
        exit(1);
    }

    return true;

}
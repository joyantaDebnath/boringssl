#ifndef MC_TLS_SQL_H

#include<mysql/mysql.h>
#include<string.h>
#include <string>

#define MC_TLS_SQL_H

struct TLS13state {
  int test_server_id;
  bool session_id_set;
  bool random_set;
  bool handshake_key_set;
  bool handshake_iv_set;
  bool application_key_set;
  bool handshake_secret_set;
  bool master_secret_set;
  bool application_iv_set;
  bool error_status;
  bool terminated;

  char message_received[100];
  char message_sent[100];
  char message_expected[100];
};



struct mc_tls_state_info {
    int id;
    int data;
    int ref_variable;
};
bool add_new_state( struct TLS13state state, int state_counter);




#endif
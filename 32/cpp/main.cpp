#define COMMAND_COUNT 10
#define USERS_COUNT 2
#define SHADOW_COUNT 2
#define USERS_COUNT 2

int userselect = 0;
bool prem();
struct _users{
    char id[4];
    char user[50];
    char name[50];
    char passwd[50];


};
struct _commands{
    const char* command;
    const char* des;


};


_users users[USERS_COUNT] = {
    {"0", "root", "ghost","1234512"},
    {"1", "ghost", "Ghaith","12345612"}
}; 
_commands commands[COMMAND_COUNT] = {
    {"","When user Press enter"},


    {"ls", "Lists the files and directories in the current directory."},
    {"pwd", "Prints the current working directory (full path)."},
    {"whoami", "Displays the current user name."},
    {"id","Displays the current user id"},
    {"clear", "Clears the current screen."},
    {"exit", "Closes the current session and exits the system."},
    {"passwd", "Change user Password."},
    {"help", "Displays a list of available commands with their descriptions."},
    {"sha", "Encode String with sha256"}


}; 

bool check_execute(char* str);

uint8_t strContains(char* string, char* toFind)
{
    uint8_t slen = strlen(string);
    uint8_t tFlen = strlen(toFind);
    uint8_t found = 0;

    if( slen >= tFlen )
    {
        for(uint8_t s=0, t=0; s<slen; s++)
        {
            do{

                if( string[s] == toFind[t] )
                {
                    if( ++found == tFlen ) return 1;
                    s++;
                    t++;
                }
                else { s -= found; found=0; t=0; }

              }while(found);
        }
        return 0;
    }
    else return -1;
}
void checkString(const char* str) {


    if (strncmp(str, "SHA", 3) == 0) {

        printf("The string starts with 'SHA'.\n");

    } else {

        printf("The string does not start with 'SHA'.\n");

    }

}
bool check_execute(char* str){
    // checkString(str);
    
    if (strcmp(str, "clear") == 0) {
        clear(); // clear the screen
        
    }
    else if (strcmp(str, "whoami") == 0) {
        printf("\nid=");
        printf(users[userselect].id);
        printf(" (");
        printf(users[userselect].user);
        printf(")");
        
        
    }
    else if (strcmp(str, "id") == 0) {
        printf("\nid=");
        printf(users[userselect].id);
        
        
        
    }
    else if (strcmp((const char*)str, "passwd") == 0) {
        char passwd[50];

        printf("\nChange password for ");
        printf(users[userselect].user);
        printf("\nCurrent password: ");
        scanf(passwd, sizeof(passwd));
        // printf(users[userselect].passwd);
        if (strcmp(passwd, users[userselect].passwd) == 0)
        {

            printf("\nNew password: ");
            scanf(passwd, sizeof(passwd));
            int i = 0;
            
            for (i; passwd[i] != '\0' && i < 49; i++) {
                users[userselect].passwd[i] = passwd[i];

            }
            users[userselect].passwd[i] = '\0'; // END OF Bytes
            
            printf("\npasswd: password updated successfully\n");

        }else{

            printf("\npasswd: Authentication token manipulation error\npasswd: password unchanged\n");

        }

    }
    else if (strcmp(str, "exit") == 0) {
        prem();
    }else if (strcmp(str, "help") == 0) {
        printf("\n\n");
        for (int i = 1; i < COMMAND_COUNT; ++i)
        {
            printf(commands[i].command);
            printf("    ");
            printf(commands[i].des);
            printf("\n");
        }


    }
    else if (strncmp((const char*)str, "sha", 3) == 0) {
        // printf("FIND\n");
        uint32_t hash[8] = {};
        const char* new_str = str + 4;
        

        sha256(reinterpret_cast<const uint8_t*>(new_str), strlen(new_str), hash);
        printf("\n");
        print_hash(hash, 8);


    }
    else {
        // printf("%s\n");
        // printf("FIND\n");
    }

    return false;

}


bool _prem(const char* user, const char* passwd) {\
    userselect = 0;

    for (int i = 0; i < USERS_COUNT; ++i) {
        if (strcmp(user, users[i].user) == 0 && strcmp(passwd, users[i].passwd) == 0) {
            // printf("XX");
            
            
            return true; 
        }
        userselect+=1;
    }
    return false; 
}

bool prem(){
    char user[50];
    char passwd[50];
    while (true){
        printf("\nEnter username: ");
        scanf(user, sizeof(user)); 

        printf("\nEnter password: ");
        scanf(passwd, sizeof(passwd)); 
        if (_prem(user, passwd)) {
            
            printf("\nLogin successful!\n");

            break;
        } else {
            printf("\nLogin failed!\n");
        }
    }
    return true;
}
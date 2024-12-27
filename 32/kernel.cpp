#include "cpp/stdint.cpp"
#include "cpp/string.cpp"
#include "cpp/io/stdio.cpp"
#include "cpp/sha256.cpp"
#include "cpp/main.cpp"


#define TICKS_PER_SECOND 1000000000 

int x = 42;

void r(){
        printf("\n");
        printf(users[userselect].user);
        printf("@");
        printf(users[userselect].name);
        printf(":# ");
}



void int_to_hex(uint32_t num, char* str) {
    for (int i = 0; i < 8; i++) {
        str[i] = "0123456789abcdef"[(num >> ((7 - i) * 4)) & 0x0F];
    }
    str[8] = '\0'; 
}
bool hash_starts_with_zeros(uint32_t* hash, int target_zeros) {
    char hash_string[65];
    for (int i = 0; i < 8; i++) {
        int_to_hex(hash[i], hash_string + (i * 8)); 
    }

    for (int j = 0; j < target_zeros; j++) {
        if (hash_string[j] != '0') {
            return false; 
        }
    }
    return true;
}




// void checkString(const char* str) {


//     if (strncmp(str, "SHA", 3) == 0) {

//         printf("he string starts with 'SHA'.\n");

//     } else {

//         printf("The string does not start with SHA.\n");

//     }

// }

extern "C" void main() {
    


    uint64_t start_time = __builtin_ia32_rdtsc();




    clear();
    const char* str1 = "Kernel Start...\nPlease Wait...\n";
    printf(str1);
    


    


    
    char buffer[50];
    uint32_t size = sizeof(buffer);
    
    // printf(buffer);
    uint32_t hash[8] = {};
    int i =0;

    int n =0;

    while(true){
        snprintf(buffer, size, "%dfofU9$1 1v290$=+o%d", i, i);
        sha256(reinterpret_cast<const uint8_t*>(buffer), strlen(buffer), hash);
        
        
        if (hash_starts_with_zeros(hash, 4) || hash_starts_with_zeros(hash, 5) || hash_starts_with_zeros(hash, 6) || hash_starts_with_zeros(hash, 10) || hash_starts_with_zeros(hash, 11) ||
            hash_starts_with_zeros(hash, 12) || hash_starts_with_zeros(hash, 13) ||
            hash_starts_with_zeros(hash, 14) || hash_starts_with_zeros(hash, 15) || hash_starts_with_zeros(hash, 16) || hash_starts_with_zeros(hash, 17)
            || hash_starts_with_zeros(hash, 18)||
            hash_starts_with_zeros(hash, 19)
            || hash_starts_with_zeros(hash, 20)
            ) {
            printf("\n");
            printf(buffer);
            printf("\n");
            printf("FOUND\n");
            print_hash(hash, 8);
            // break;
            // break;
            n++;
            if (n > 4)
            {
                break;
            }
        }
        i++;
    }



    

    
    
    

    
    

    
    

    
    prem();

    


    char input[50];
    
    // set_cursor_position(10, 20); // Set cursor position
    
    while (True) {
        r();

        char c[50];
        uint32_t s  =  sizeof(c);
        scanf(input, sizeof(input));
        bool isFound = false;
        for (int i = 0; i < COMMAND_COUNT; i++) {
            // checkString(input);
            size_t command_size = sizeof(commands[i].command);


            // snprintf(c, s, "\nc: %s, %s, %d\n", commands[i].command, input, command_size-1);
            // snprintf(buffer, size, "block data%d", i);
            // printf(c);
            if (strncmp(input, commands[i].command, command_size-1) == 0) {
                isFound = true;
   
                check_execute(input);
                
                break;
            }
        }
        if (!isFound)
        {
            printf("\nCommand Not Found");
        }
        

    
    }

    return;
}

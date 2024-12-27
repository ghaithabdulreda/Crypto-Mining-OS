#define VIDEO_BUF_PTR 0xb8000
#define VIDEO_WIDTH (80) 
#define VIDEO_HEIGHT (25)
#define CURSOR_PORT (0x3D5) 
#define PIC1_PORT (0x20)       


int position = 0; // CURSOR POS

void printf(const char* str1);
void print(const char* str1, ...);
void clear();
void scanf(char* input);
void set_cursor_position(unsigned char row, unsigned char col);
static inline unsigned char inb(unsigned short port);
static inline void outb(unsigned short port, unsigned char data);

size_t strlen(const char* str) {
    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}




const char* scancodeInputData(char scancode) {
    switch(scancode) {
        case 0x00: 
            return "ERROR";
        case 0x01: 
            return "ESC";
        case 0x02: 
            return "1";
        case 0x03: 
            return "2";
        case 0x04: 
            return "3";
        case 0x05: 
            return "4";
        case 0x06: 
            return "5";
        case 0x07: 
            return "6";
        case 0x08: 
            return "7";
        case 0x09: 
            return "8";
        case 0x0A: 
            return "9";
        case 0x0B: 
            return "0";
        case 0x0C: 
            return "-";
        case 0x0D: 
            return "=";
        case 0x0E: 
            return "BACKSPACE";
        case 0x0F: 
            return "TAB";
        case 0x10: 
            return "q"; // Uppercase
        case 0x11: 
            return "w"; // Uppercase
        case 0x12: 
            return "e"; // Uppercase
        case 0x13: 
            return "r"; // Uppercase
        case 0x14: 
            return "t"; // Uppercase
        case 0x15: 
            return "y"; // Uppercase
        case 0x16: 
            return "u"; // Uppercase
        case 0x17: 
            return "i"; // Uppercase
        case 0x18: 
            return "o"; // Uppercase
        case 0x19: 
            return "p"; // Uppercase
        case 0x1A: 
            return "["; // Uppercase
        case 0x1B: 
            return "]"; // Uppercase
        case 0x1C: 
            return "ENTER";
        case 0x1D: 
            return "CONTROL";
        case 0x1E: 
            return "a"; // Uppercase
        case 0x1F: 
            return "s"; // Uppercase
        case 0x20: 
            return "d"; // Uppercase
        case 0x21: 
            return "f"; // Uppercase
        case 0x22: 
            return "g"; // Uppercase
        case 0x23: 
            return "h"; // Uppercase
        case 0x24: 
            return "j"; // Uppercase
        case 0x25: 
            return "k"; // Uppercase
        case 0x26: 
            return "l"; // Uppercase
        case 0x27: 
            return ";"; // Uppercase
        case 0x28: 
            return "'"; // Uppercase
        case 0x29: 
            return "`"; // Uppercase
        case 0x2A: 
            return "SHIFT";
        case 0x2B: 
            return "\\"; // Uppercase
        case 0x2C: 
            return "z"; // Uppercase
        case 0x2D: 
            return "x"; // Uppercase
        case 0x2E: 
            return "c"; // Uppercase
        case 0x2F: 
            return "V"; // Uppercase
        case 0x30: 
            return "b"; // Uppercase
        case 0x31: 
            return "n"; // Uppercase
        case 0x32: 
            return "m"; // Uppercase
        case 0x33: 
            return ","; // Uppercase
        case 0x34: 
            return "."; // Uppercase
        case 0x35: 
            return "/"; // Uppercase
        case 0x36: 
            return "SHIFT";
        case 0x37: 
            return "*";
        case 0x38: 
            return "ALT"; // Alternate key
        case 0x39: 
            return " ";
        case 0x3A: 
            return "CAPSLOCK";
        case 0x3B: 
            return "F1";
        case 0x3C: 
            return "F2";
        case 0x3D: 
            return "F3";
        case 0x3E: 
            return "F4";
        case 0x3F: 
            return "F5";
        case 0x40: 
            return "F6";
        case 0x41: 
            return "F7";
        case 0x42: 
            return "F8";
        case 0x43: 
            return "F9";
        case 0x44: 
            return "F10";
        case 0x45: 
            return "NUMLOCK";
        case 0x46: 
            return "SCROLLLOCK";
        case 0x47: 
            return "7";
        case 0x48: 
            return "8";
        case 0x49: 
            return "9";
        case 0x4A: 
            return "-";
        case 0x4B: 
            return "4";
        case 0x4C: 
            return "5";
        case 0x4D: 
            return "6";
        case 0x4E: 
            return "+";
        case 0x4F: 
            return "1";
        case 0x50: 
            return "2";
        case 0x51: 
            return "3";
        case 0x52: 
            return "0";
        case 0x53: 
            return ".";
        
   

        default: 
            return "UNKNOWN";
    }
}


void print(const char* str1, ...){}
void printf(const char* str1) {
    volatile char* video_memory = (volatile char*) VIDEO_BUF_PTR;
    unsigned char color = 7; 
    if (strcmp(str1, "BACKSPACE") ==0) // WHEN BACKSPACE
    {
        position-=2;
        set_cursor_position(position / 2 / 80, position / 2 % 80);
        video_memory[position] = ' ';    
        video_memory[position + 1] = color;    

        return;
    }

    for (int i = 0; str1[i] != '\0'; i++) {
        if (str1[i] == '\n') {
            int line_size = 80;  
            position = (position / (line_size * 2) + 1) * (line_size * 2); 
            set_cursor_position(position / 2 / 80, position / 2 % 80); 
        } else {
            video_memory[position] = str1[i];     
            video_memory[position + 1] = color;     
            position += 2;
            set_cursor_position(position / 2 / 80, position / 2 % 80);
        }
        
      
        if (position >= VIDEO_WIDTH * VIDEO_HEIGHT * 2) {
            clear(); 
            position = 0;
        }
    }
}



void clear() {
    volatile char* video_memory = (volatile char*) VIDEO_BUF_PTR;
    unsigned char color = 7; 

    for (int i = 0; i < 80 * 25 * 2; i += 2) {
        video_memory[i] = ' ';   
        video_memory[i + 1] = color;  
    }

    position = 0;
}


void scanf(char* input, int max_size) {
    int p = 0;
    unsigned char scan_code;

    while (1) {
        if (inb(0x64) & 0x01) {
            scan_code = inb(0x60);
            if (scan_code < 128) {
            	const char* char_input = scancodeInputData(scan_code);
            	if (char_input == "ENTER")
            		break;
            	else if(char_input == "BACKSPACE"){
                    if (p != 0)
                    {
                        p--;
                        printf("BACKSPACE");
                    }
                    
                    

                }
                else{
                    printf(char_input);
                    input[p] = char_input[0];
                    p++;
                }
            }
        }

        
        if (p >= max_size - 1) {
            break;
        }
    }
    
    input[p] = '\0'; 
}
void sleep(int seconds) {
    volatile int count = 0; // استخدام volatile لتجنب تحسين الكود
    for (int i = 0; i < seconds * 1000000; i++) {
        count++;
    }
}


void set_cursor_position(unsigned char row, unsigned char col) {
    unsigned short position = (row * 80) + col;
    // Change the cursor position
    outb(0x3D4, 0x0F);
    outb(0x3D5, position & 0xFF);
    outb(0x3D4, 0x0E);
    outb(0x3D5, (position >> 8) & 0xFF);
}
void enable_cursor() {
    outb(0x3D4, 0x0A); 
    outb(0x3D5, 0x20); 
}

void disable_cursor() {
    outb(0x3D4, 0x0A); 
    outb(0x3D5, 0x20); 
}


static inline unsigned char inb(unsigned short port) {
    unsigned char ret;
    __asm__ __volatile__("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

static inline void outb(unsigned short port, unsigned char data) {
    __asm__ __volatile__("outb %0, %1" : : "a"(data), "Nd"(port));
}





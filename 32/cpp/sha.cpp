
// تعريف بعض العمليات الأساسية للخوارزمية SHA-256
#define ROTR(x, n) (((x) >> (n)) | ((x) << (32 - (n))))
#define SHR(x, n) ((x) >> (n))
#define Ch(x, y, z) (((x) & (y)) ^ (~(x) & (z)))
#define Maj(x, y, z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define Sigma0(x) (ROTR(x, 2) ^ ROTR(x, 13) ^ ROTR(x, 22))
#define Sigma1(x) (ROTR(x, 6) ^ ROTR(x, 11) ^ ROTR(x, 25))
#define sigma0(x) (ROTR(x, 7) ^ ROTR(x, 18) ^ SHR(x, 3))
#define sigma1(x) (ROTR(x, 17) ^ ROTR(x, 19) ^ SHR(x, 10))

// القيم الابتدائية لـ SHA-256
uint32_t H[8] = {
    0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
    0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
};

// ثوابت SHA-256
uint32_t K[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
    0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
    0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
    0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
    0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
    0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
    0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

// دالة لتشفير رسالة نصية
void sha256_transform(uint32_t *hash, const uint8_t *data) {
    uint32_t W[64];
    for (int i = 0; i < 16; i++) {
        W[i] = (data[i * 4] << 24) | (data[i * 4 + 1] << 16) |
               (data[i * 4 + 2] << 8) | (data[i * 4 + 3]);
    }
    
    for (int i = 16; i < 64; i++) {
        W[i] = sigma1(W[i - 2]) + W[i - 7] + sigma0(W[i - 15]) + W[i - 16];
    }
    
    uint32_t a = hash[0];
    uint32_t b = hash[1];
    uint32_t c = hash[2];
    uint32_t d = hash[3];
    uint32_t e = hash[4];
    uint32_t f = hash[5];
    uint32_t g = hash[6];
    uint32_t h = hash[7];

    for (int i = 0; i < 64; i++) {
        uint32_t temp1 = h + Sigma1(e) + Ch(e, f, g) + K[i] + W[i];
        uint32_t temp2 = Sigma0(a) + Maj(a, b, c);
        h = g;
        g = f;
        f = e;
        e = d + temp1;
        d = c;
        c = b;
        b = a;
        a = temp1 + temp2;
    }

    hash[0] += a;
    hash[1] += b;
    hash[2] += c;
    hash[3] += d;
    hash[4] += e;
    hash[5] += f;
    hash[6] += g;
    hash[7] += h;
}

// دالة البادئة لتجهيز الرسالة
void sha256_init_message(const uint8_t *message, size_t len, uint8_t *paddedMessage, size_t &paddedLen) {
    size_t totalLen = len + 1 + 8;
    paddedLen = (totalLen % 64 == 0) ? totalLen : totalLen + (64 - (totalLen % 64));
    
    for (size_t i = 0; i < len; i++) {
        paddedMessage[i] = message[i];
    }
    paddedMessage[len] = 0x80; // بت النهاية

    for (size_t i = len + 1; i < paddedLen - 8; i++) {
        paddedMessage[i] = 0x00;
    }

    uint64_t bitLen = len * 8;
    for (int i = 0; i < 8; i++) {
        paddedMessage[paddedLen - 1 - i] = (bitLen >> (i * 8)) & 0xFF;
    }
}

// الدالة الرئيسية
void sha256(const uint8_t *message, size_t len, uint32_t *output) {
    uint8_t paddedMessage[64 * ((len + 72) / 64)]; // حجم الرسالة المبطنة
    size_t paddedLen;
    
    sha256_init_message(message, len, paddedMessage, paddedLen);

    for (int i = 0; i < 8; i++) {
        output[i] = H[i];
    }

    for (size_t i = 0; i < paddedLen; i += 64) {
        sha256_transform(output, paddedMessage + i);
    }
}
void uint32_to_hex(uint32_t num, char* buffer) {
    const char* hex_digits = "0123456789abcdef";
    for (int i = 7; i >= 0; i--) {
        buffer[i] = hex_digits[num & 0xF];
        num >>= 4;
    }
    buffer[8] = '\0'; 
}

void print_hash(const uint32_t* hash, int hash_len) {
    char buffer[9];
    for (int i = 0; i < hash_len; i++) {
        uint32_to_hex(hash[i], buffer);
        printf(buffer);
    }
    printf("\n"); 
}

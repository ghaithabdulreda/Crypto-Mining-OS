// تعريف دالة my_snprintf
int snprintf(char* buffer, uint32_t size, const char* format, ...) {
    if (!buffer || size == 0) {
        return -1; // تحقق من صحة المعطيات
    }

    uint32_t written = 0; // عدد الأحرف المكتوبة
    const char* ptr = format; // مؤشر على بداية سلسلة التنسيق

    // بداية استخدام المعطيات المتغيرة
    uint32_t* args = (uint32_t*)(&format + 1); // تخزين عنوان المعطيات المتغيرة

    while (*ptr != '\0' && written < size - 1) { // حتى نهاية السلسلة
        if (*ptr == '%') { // إذا كان هناك رمز تنسيق
            ptr++; // الانتقال إلى الرمز التالي
            if (*ptr == 'd') { // تنسيق للأعداد الصحيحة
                int value = (int)(*args); // الحصول على القيمة التالية
                args++; // الانتقال إلى المعطى التالي
                // تحويل العدد إلى سلسلة
                char temp[20]; // تخزين مؤقت للتحويل
                int len = 0;
                if (value < 0) {
                    temp[len++] = '-';
                    value = -value;
                }
                // تحويل العدد إلى سلسلة
                do {
                    temp[len++] = (value % 10) + '0';
                    value /= 10;
                } while (value > 0);

                // عكس السلسلة
                for (int j = len - 1; j >= 0; j--) {
                    if (written < size - 1) {
                        buffer[written++] = temp[j];
                    }
                }
            } else if (*ptr == 's') { // تنسيق للسلاسل النصية
                const char* str = (const char*)*args; // الحصول على السلسلة
                args++; // الانتقال إلى المعطى التالي
                while (*str != '\0' && written < size - 1) {
                    buffer[written++] = *str++;
                }
            } else if (*ptr == 'c') { // تنسيق للأحرف
                char c = (char)(*args); // الحصول على الحرف
                args++; // الانتقال إلى المعطى التالي
                buffer[written++] = c;
            }
            // انتقل إلى الرمز التالي
            ptr++;
        } else {
            // إضافة الحرف العادي
            buffer[written++] = *ptr;
            ptr++;
        }
    }

    buffer[written] = '\0'; // إنهاء السلسلة
    return written; // إرجاع عدد الأحرف المكتوبة
}

int strcmp(const char* str1, const char* str2) {
    int i = 0;

    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return str1[i] - str2[i];
        }
        i++;
    }

    return str1[i] - str2[i];
}



int strncmp(const char* str1, const char* str2, uint8_t n) {

    while (n > 0) {

        if (*str1 == '\0' && *str2 == '\0') {

            return 0; // السلسلتان متساويتان

        }

        

        if (*str1 == '\0' || *str2 == '\0' || *str1 != *str2) {

            return (unsigned char)(*str1) - (unsigned char)(*str2); // إرجاع الفرق

        }


        str1++;

        str2++;

        n--;

    }


    return 0; // إذا تم مقارنة n أحرف ولم يكن هناك اختلاف

}

void split(const char* input, const char* delimiter, char* result) {
    // مقارنة المدخلات بالحدود الفاصلة
    int w = strncmp(input, delimiter, sizeof(delimiter));

    // تنسيق النتيجة
    snprintf(result, 8, "c: %d", w); // تأكد من أن الحجم كافٍ
}
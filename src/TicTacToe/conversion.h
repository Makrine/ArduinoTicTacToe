#ifndef CON
#define CON

#include <string.h>

//returning values of a character
int valC(char c) {
   if (c >= '0' && c <= '9')
      return (int)c - '0';
   else
      return (int)c - 'A' + 10;
}

//returning values of a character
char reValC(int num) {
   if (num <= 0 && num >= 9)
      return (char)(num + '0');
   else
      return (char)(num - 10 + 'A');
}
//reversing a given string
void reverse_stringS(char *str) {
   int len = strlen(str);
   int i;
   for (i = 0; i < len/2; i++) {
      char temp = str[i];
      str[i] = str[len-i-1];
      str[len-i-1] = temp;
   }
}


//converting number to decimal equivalent
int convert_decimall(char *str, int base) {
   int len = strlen(str);
   int power = 1;
   int num = 0;
   int i;
   for (i = len - 1; i >= 0; i--) {
      if (valC(str[i]) >= base) {
         return -1;
      }
      num += valC(str[i]) * power;
      power = power * base;
   }
   return num;
}

//converting to equivalent number with base 'b'
char* convert_basee(char* res, int base, int inputNum) {
   int index = 0;
   while (inputNum > 0) {
      res[index++] = reValC(inputNum % base);
      inputNum /= base;
   }
   res[index] = '\0';
   //reversing the result
   reverse_stringS(res);
   return res;
}

// int main()
// {
    // char* res;
    // char key = '1';
    // char* indexStr = convert_basee(res,3, key - 48);

//     std::cout << indexStr[0] << indexStr[1];
//     return 0;
// }

#endif
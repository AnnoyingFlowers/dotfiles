// #include <stdio.h>
// #include <string.h>

// // 辅助函数，用于反转字符串
// void reverse(char *str, int len) {
//     int i = 0, j = len - 1;
//     while (i < j) {
//         char temp = str[i];
//         str[i] = str[j];
//         str[j] = temp;
//         i++;
//         j--;
//     }
// }

// // 将整数转换为十六进制字符串
// int int_to_hex(unsigned int value, char *str) {
//     int i = 0;
//     int remain;

//     // 处理0的特殊情况
//     if (value == 0) {
//         str[i++] = '0';
//         str[i] = '\0';
//         return i;
//     }

//     // 转换整数为十六进制字符串
//     while (value != 0) {
//         remain = value % 16;
//         if (remain < 10) {
//             str[i++] = remain + '0';
//         } else {
//             str[i++] = (remain - 10) + 'a';  // 使用小写字母
//         }
//         value = value / 16;
//     }

//     str[i] = '\0';  // 添加字符串结束符

//     reverse(str, i);  // 反转字符串

//     return i;  // 返回字符串长度
// }

// int main() {
//     int num = -2147483647;  // 例子中的整数
//     char hex_str[20];       // 存储十六进制字符串

//     int_to_hex(num, hex_str);

//     printf("十六进制形式的字符串是: %s\n", hex_str);

//     return 0;
// }
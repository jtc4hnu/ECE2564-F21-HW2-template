int main(void)
{
    unsigned int a = 0x1337c0d3;  // what is the decimal value of a?
    unsigned int b = 0xfffffffe;  // what is the decimal value of b?

    // Use a calculator to multiply decimal values of a and b and compare the result to c
    unsigned int c = a * b;

    signed int x = a;    // what is the decimal value of x?
    signed int y = b;    // what is the decimal value of y?

    // compare z to what you expect x * y should be
    signed int z = x * y;
}

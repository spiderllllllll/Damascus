
int extract(unsigned int x, int a[]) {

    int i, count;

    count = 0;

    for(i = 0; x; i++) {
        if(x & 1) 
            a[count++] = i;
        x = x >> 1;
    }

    return count;
}


int popcount(unsigned int x)
{
    x = x - ((x >> 1) & 0x55555555);
    x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
    x = (x + (x >> 4)) & 0x0F0F0F0F;
    x = x + (x >> 8);
    x = x + (x >> 16);
    return x & 0x0000003F;
}


int parity(unsigned int v) { 
    v ^= v >> 16;
    v ^= v >> 8;
    v ^= v >> 4;
    v &= 0xf;
    return (0x6996 >> v) & 1;
}


int msb(unsigned int n) 
{ 
    n |= n >> 1; 
    n |= n >> 2; 
    n |= n >> 4; 
    n |= n >> 8; 
    n |= n >> 16; 
    n = n + 1; 
    return (n >> 1); 
}
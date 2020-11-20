

#include "Advanced.h"


void Noise( int n, unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
    int x, k, y = 0;
    int num_noise_pixels = 0;

    srand (time(NULL));
    /*with respect to time, it will generate a random digit*/

    num_noise_pixels = n * WIDTH * HEIGHT / 100;
    /*sets a number of pixels to be targeted due to the percentage and width and height*/

    for(k = 0 ;k<num_noise_pixels ;k++){
        x = rand() % WIDTH;
        y = rand() % HEIGHT;
        R[x][y] = G[x][y] = B[x][y] = 255;
        /*randomly changed the pixels to white noise*/
    }
}

void Posterize(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], unsigned int rbits, unsigned int gbits, unsigned int bbits)
{
    int x, y, z;
    int r, g, b;
    for( y = 0; y < HEIGHT; y++ )
    {
        for( x = 0; x < WIDTH; x++ )
        {
            r = R[x][y];
            for(z = 0; z < rbits ; z++)
            {
                r = (r >> 1);
            }
            r = (r << 1);
            for(z = 0; z < rbits - 1 ; z++)
            {
                r = (r << 1) + 1;
            }
            R[x][y] = r;

            g = G[x][y];
            for(z = 0; z < gbits ; z++)
            {
                g = (g >> 1);
            }
            g = (g << 1);
            for(z = 0; z < gbits - 1 ; z++)
            {
                g = (g << 1) + 1;
            }
            G[x][y] = g;

            b = B[x][y];
            for(z = 0; z < bbits ; z++)
            {
                b = (b >> 1);
            }
            b = (b << 1);
            for(z = 0; z < bbits - 1 ; z++)
            {
                b = (b << 1) + 1;
            }
            B[x][y] = b;
        }
    }
}

void MotionBlur(int BlurAmount, unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
    int x, y, z;
    int r, g, b;

    int NewR[WIDTH][HEIGHT];
    int NewG[WIDTH][HEIGHT];
    int NewB[WIDTH][HEIGHT];

    for (x = 0; x < WIDTH; x++) {
        NewR[x][0] = R[x][0];
        NewG[x][0] = G[x][0];
        NewB[x][0] = B[x][0];
        NewR[x][1] = R[x][0]/2 + R[x][1]/2;
        NewG[x][1] = G[x][0]/2 + G[x][1]/2;
        NewB[x][1] = B[x][0]/2 + B[x][1]/2;
    }

    for( y = 2; y < HEIGHT; y++ ) {
        for (x = 0; x < WIDTH; x++) {
            r = g = b = 0;
            if ( y < BlurAmount)
            {
                for (z = 1; z <= y; z++){
                    r = r + R[x][y-z];
                    g = g + G[x][y-z];
                    b = b + B[x][y-z];
                }
                NewR[x][y] = R[x][y]/2 + r/(2*y);
                NewG[x][y] = G[x][y]/2 + g/(2*y);
                NewB[x][y] = B[x][y]/2 + b/(2*y);
            }
            else
            {
                for (z = 1; z <= BlurAmount ; z++){
                    r = r + R[x][y-z];
                    g = g + G[x][y-z];
                    b = b + B[x][y-z];
                }
                NewR[x][y] = R[x][y]/2 + r/(2*BlurAmount);
                NewG[x][y] = G[x][y]/2 + g/(2*BlurAmount);
                NewB[x][y] = B[x][y]/2 + b/(2*BlurAmount);
            }
        }
    }
    for( y = 0; y < HEIGHT; y++ ) {
        for (x = 0; x < WIDTH; x++) {
            R[x][y] = NewR[x][y];
            G[x][y] = NewG[x][y];
            B[x][y] = NewB[x][y];
        }
    }
}


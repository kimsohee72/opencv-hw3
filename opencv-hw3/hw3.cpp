#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

Mat G_filtering(Mat image, int n,int row, int col) {
    unsigned char* pData = (unsigned char*)image.data;
    int size = 2 * n + 1;
    int l = 0,c=0;
    int* count = new int[image.cols]();
    Mat filter(2*n+1, 2 * n + 1, CV_8UC1, Scalar(0));
    /*for (int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols; j++) {
            for (int k = -n; k <= n; k++) {
                if (i + k >= 0 && i + k < image.rows) {
                    count[l]=k;
                    l++;
                }
            }
            for (int k = -n; k <= n; k++) {
                if (j + k >= 0 && j + k < image.cols) {
                    for (int h = 0; h < l; h++) {
                        filter[i * image.rows + j] += pData[i + image.rows * k + count[h] + 3 * j];
                    }
                }
            }
            filter[i * image.rows + j] /= size * size;
        }
    }*/
    /*for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            l = 0;
            for (int k = -1; k <= 1; k++) {
                if (i + k >= 0 && i + k < 3) {
                    count[l] = k;
                    l++;
                }
            }
            for (int k = -1; k <= 1; k++) {
                if (j + k >= 0 && j + k < 3) {
                    if (l < 3 && i - count[0] - 1 >= 0) {
                        for (int h = 0; h < l; h++) {
                            cout << (int)(i + 3 * k + count[h] + 3 * j) << " ";
                        }
                        for (int h = 0; h < 3 - l; h++) {
                            cout << "a ";
                        }
                    }
                    else if(l < 3 && i - count[0] - 1 < 0) {
                        for (int h = 0; h < 3 - l; h++) {
                            cout << "a ";
                        }
                        for (int h = 0; h < l; h++) {
                            cout << (int)(i + 3 * k + count[h] + 3 * j) << " ";
                        }
                    }
                    else {
                        for (int h = 0; h < l; h++) {
                            cout << (int)(i + 3 * k + count[h] + 3 * j) << " ";
                        }
                    }
                }
                else {
                    for (int p = 0; p < 3; p++) {
                        cout << "a ";
                    }
                }
            }
            cout << "\n";
        }
    }*/
    for (int k = -n; k <= n; k++) {
        if (row + k >= 0 && row + k < image.cols) {
            count[l] = k;
            l++;
        }
    }

    
    for (int k = -n; k <= n; k++) {
        if (col + k >= 0 && col + k < image.rows) {
            if (l <  size && row - count[0] + 1 >= image.cols) {
                for (int h = 0; h < l; h++) {
                    filter.data[c] = (int)pData[row + image.cols * k + count[h] + image.cols * col];
                    c++;
                }
                for (int h = 0; h < size - l; h++) {
                    filter.data[c] = 0;
                    c++;
                }
            }
            else if (l < size && row + count[0] - 1 < 0) {
                for (int h = 0; h < size - l; h++) {
                    filter.data[c] = 0;
                    c++;
                }
                for (int h = 0; h < l; h++) {
                    filter.data[c] = (int)pData[row + image.cols * k + count[h] + image.cols * col];
                    c++;
                }
            }
            else {
                for (int h = 0; h < l; h++) {
                    filter.data[c] = (int)pData[row + image.cols * k + count[h] + image.cols * col];
                    c++;
                }
            }
        }
        else {
            for (int p = 0; p < size; p++) {
                filter.data[c] = 0;
                c++;
            }
        }
    }

    return filter;
}

Mat RGB_filtering(Mat image, int n, int row, int col) {
    unsigned char* pData = (unsigned char*)image.data;
    int size = 2 * n + 1;
    int l = 0, c = 0;
    int* count = new int[image.rows]();
    Mat filter(2 * n + 1, 2 * n + 1, CV_8UC3, Scalar(0));

    for (int k = -n; k <= n; k++) {
        if (row + k >= 0 && row + k < image.cols) {
            count[l] = k;
            l++;
        }
    }


    for (int k = -n; k <= n; k++) {
        if (col + k >= 0 && col + k < image.rows) {
            if (l < size && row - count[0] + 1 >= image.cols) {
                for (int h = 0; h < l; h++) {
                    filter.data[c] = pData[row * 3 + image.cols * k *3 + count[h] * 3 + image.cols * col * 3];
                    c++;
                    filter.data[c] = pData[row * 3 + image.cols * k * 3 + count[h] * 3 + image.cols * col * 3 +1];
                    c++;
                    filter.data[c] = pData[row * 3 + image.cols * k * 3 + count[h] * 3 + image.cols * col * 3 +2];
                    c++;
                }
                for (int h = 0; h < size - l; h++) {
                    filter.data[c] = 0;
                    c++;
                    filter.data[c] = 0;
                    c++;
                    filter.data[c] = 0;
                    c++;
                }
            }
            else if (l < size && row + count[0] - 1 < 0) {
                for (int h = 0; h < size - l; h++) {
                    filter.data[c] = 0;
                    c++;
                    filter.data[c] = 0;
                    c++;
                    filter.data[c] = 0;
                    c++;
                }
                for (int h = 0; h < l; h++) {
                    filter.data[c] = pData[row * 3 + image.cols * k * 3 + count[h] * 3 + image.cols * col * 3];
                    c++;
                    filter.data[c] = pData[row * 3 + image.cols * k * 3 + count[h] * 3 + image.cols * col * 3 + 1];
                    c++;
                    filter.data[c] = pData[row * 3 + image.cols * k * 3 + count[h] * 3 + image.cols * col * 3 + 2];
                    c++;
                }
            }
            else {
                for (int h = 0; h < l; h++) {
                    filter.data[c] = pData[row * 3 + image.cols * k * 3 + count[h] * 3 + image.cols * col * 3];
                    c++;
                    filter.data[c] = pData[row * 3 + image.cols * k * 3 + count[h] * 3 + image.cols * col * 3 + 1];
                    c++;
                    filter.data[c] = pData[row * 3 + image.cols * k * 3 + count[h] * 3 + image.cols * col * 3 + 2];
                    c++;
                }
            }
        }
        else {
            for (int p = 0; p < size; p++) {
                filter.data[c] = 0;
                c++;
                filter.data[c] = 0;
                c++;
                filter.data[c] = 0;
                c++;
            }
        }
    }

    return filter;
}

Mat G_Moving_average(Mat G_image,int n) {
    Mat average_image(G_image.rows, G_image.cols, CV_8UC1, Scalar(0));
    Mat filter(2*n+1, 2 * n + 1, CV_8UC1, Scalar(0));
    int size = (2 * n + 1) * (2 * n + 1);
    for (int i = 0; i < G_image.rows; i++) {
        for (int j = 0; j < G_image.cols; j++) {
            filter = G_filtering(G_image, n, j, i);
            int sum = 0;
            for (int k = 0; k < size; k++) {
                sum += filter.data[k];
            }

            average_image.data[i * G_image.cols + j] = sum / size;


        }
        cout << "\n";
    }
    imshow("moving average image", average_image);

    return average_image;
}

Mat RGB_Moving_average(Mat image, int n) {
    Mat average_image(image.rows, image.cols, CV_8UC3, Scalar(0));
    Mat filter(2 * n + 1, 2 * n + 1, CV_8UC3, Scalar(0));
    int size = (2 * n + 1) * (2 * n + 1);
    for (int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols; j++) {
            filter = RGB_filtering(image, n, j, i);
            int r_sum = 0;
            int b_sum = 0;
            int g_sum = 0;
            for (int k = 0; k < size * 3; k++) {
                if (k % 3 == 0) {
                    b_sum += (int)filter.data[k];
                }
                else if (k % 3 == 1) {
                    g_sum += (int)filter.data[k];
                }
                else if (k % 3 == 2) {
                    r_sum += (int)filter.data[k];
                }
            }
            
            average_image.data[i * image.cols *3 + j*3] = b_sum / (size);
            average_image.data[i * image.cols * 3 + j * 3 +1] = g_sum / (size );
            average_image.data[i * image.cols * 3 + j * 3 +2] = r_sum / (size );

        }
    }
    imshow("rgb moving average image", average_image);

    return average_image;
}

Mat G_Laplacian(Mat G_image, int n) {
    Mat lapician_image(G_image.rows, G_image.cols, CV_8UC1, Scalar(0));
    Mat filter(2 * n + 1, 2 * n + 1, CV_8UC1, Scalar(0));
    int size = (2 * n + 1) * (2 * n + 1);
    for (int i = 0; i < G_image.rows; i++) {
        for (int j = 0; j < G_image.cols; j++) {
            filter = G_filtering(G_image, n, j, i);  
            int lap= (int)filter.data[1] + (int)filter.data[3] + (int)filter.data[5] + (int)filter.data[7] - (4 * (int)filter.data[4]);
          
            if (lap < 0) {
                lapician_image.data[i * G_image.cols + j] = 0;
            }
            else {
                lapician_image.data[i * G_image.cols + j] = lap;
            }

        }
      
    }
    imshow("Gray Lapician image", lapician_image);

    return lapician_image;
}


Mat RGB_Laplacian(Mat image, int n) {
    Mat laplacian_image(image.rows, image.cols, CV_8UC3, Scalar(0));
    Mat filter(2 * n + 1, 2 * n + 1, CV_8UC3, Scalar(0));
    int size = (2 * n + 1) * (2 * n + 1);
    Mat b_data(2 * n + 1, 2 * n + 1, CV_8UC1, Scalar(0));
    Mat r_data(2 * n + 1, 2 * n + 1, CV_8UC1, Scalar(0));
    Mat g_data(2 * n + 1, 2 * n + 1, CV_8UC1, Scalar(0));
    int x=0, y=0, z=0;
    for (int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols; j++) {
            filter = RGB_filtering(image, n, j, i);
            int r = 0;
            int b = 0;
            int g = 0;
            for (int k = 0; k < size * 3; k++) {
                if (k % 3 == 0) {
                    b_data.data[x] = (int)filter.data[k];
                    x++;                   
                }
                else if (k % 3 == 1) {
                    g_data.data[y] = (int)filter.data[k];
                    y++;
                }
                else if (k % 3 == 2) {
                    r_data.data[z] = (int)filter.data[k];
                    z++;
                }
            }
            b = (int)b_data.data[1] + (int)b_data.data[3] + (int)b_data.data[5] + (int)b_data.data[7] - (4 * (int)b_data.data[4]);
            g = (int)g_data.data[1] + (int)g_data.data[3] + (int)g_data.data[5] + (int)g_data.data[7] - (4 * (int)g_data.data[4]);
            r = (int)r_data.data[1] + (int)r_data.data[3] + (int)r_data.data[5] + (int)r_data.data[7] - (4 * (int)r_data.data[4]);
            if (b < 0) {
                laplacian_image.data[i * image.cols * 3 + j * 3] = 0;
            }
            else {
                laplacian_image.data[i * image.cols * 3 + j * 3] = b;
            }
            if (g < 0) {
                laplacian_image.data[i * image.cols * 3 + j * 3+1] = 0;
            }
            else {
                laplacian_image.data[i * image.cols * 3 + j * 3+1] = g;
            }
            if (r < 0) {
                laplacian_image.data[i * image.cols * 3 + j * 3+2] = 0;
            }
            else {
                laplacian_image.data[i * image.cols * 3 + j * 3+2] = r;
            }
            

            x = 0, y = 0, z = 0;

        }
    }
    imshow("Laplacian image", laplacian_image);

    return laplacian_image;
}

Mat G_Sharpening(Mat G_image, int n) {
    Mat sharpening_image(G_image.rows, G_image.cols, CV_8UC1, Scalar(0));
    Mat filter(2 * n + 1, 2 * n + 1, CV_8UC1, Scalar(0));
    int size = (2 * n + 1) * (2 * n + 1);
    for (int i = 0; i < G_image.rows; i++) {
        for (int j = 0; j < G_image.cols; j++) {
            filter = G_filtering(G_image, n, j, i);
            /* for (int k = 0; k < size; k++) {
                 cout << (int)filter.data[k] << " ";
             }*/

            int lap = (int)filter.data[0] + (int)filter.data[1] + (int)filter.data[2] + (int)filter.data[3] + (int)filter.data[5] + (int)filter.data[6] + (int)filter.data[7] + (int)filter.data[8];
            int sum = -lap + (9 * (int)filter.data[4]);

            if (sum < 0) {
                sharpening_image.data[i * G_image.cols + j] = 0;
            }
            else if (sum > 255) {
                sharpening_image.data[i * G_image.cols + j] = 255;
            }
            else {
                sharpening_image.data[i * G_image.cols + j] = sum;
            }

        }

    }
    imshow("Gray Sharpening image", sharpening_image);

    return sharpening_image;
}

Mat RGB_Sharpening(Mat image, int n) {
    Mat sharpening_image(image.rows, image.cols, CV_8UC3, Scalar(0));
    Mat filter(2 * n + 1, 2 * n + 1, CV_8UC3, Scalar(0));
    int size = (2 * n + 1) * (2 * n + 1);
    Mat b_data(2 * n + 1, 2 * n + 1, CV_8UC1, Scalar(0));
    Mat r_data(2 * n + 1, 2 * n + 1, CV_8UC1, Scalar(0));
    Mat g_data(2 * n + 1, 2 * n + 1, CV_8UC1, Scalar(0));
    int* sharpening = new int[3]();
    int x = 0, y = 0, z = 0;

    for (int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols; j++) {
            filter = RGB_filtering(image, n, j, i);
            
            for (int k = 0; k < size * 3; k++) {
                if (k % 3 == 0) {
                    b_data.data[x] = (int)filter.data[k];
                    x++;
                }
                else if (k % 3 == 1) {
                    g_data.data[y] = (int)filter.data[k];
                    y++;
                }
                else if (k % 3 == 2) {
                    r_data.data[z] = (int)filter.data[k];
                    z++;
                }
            }
            sharpening[0] = 0;
            sharpening[1] = 0;
            sharpening[2] = 0;
            
            for (int m = 0; m < 9; m++) {
                if (m != 4) {
                    sharpening[0] -= (int)b_data.data[m];
                    sharpening[1] -= (int)g_data.data[m];
                    sharpening[2] -= (int)r_data.data[m];
                }
            }
            sharpening[0] += 9*((int)b_data.data[4]);
            sharpening[1] += 9*((int)g_data.data[4]);
            sharpening[2] += 9*((int)r_data.data[4]);

            for (int m = 0; m < 3; m++) {
                if (sharpening[m] < 0) {
                    if (m == 0) {
                        sharpening_image.data[i * image.cols * 3 + j * 3] = 0;
                    }
                    else if (m == 1) {
                        sharpening_image.data[i * image.cols * 3 + j * 3 + 1] = 0;
                    }
                    else if (m == 2) {
                        sharpening_image.data[i * image.cols * 3 + j * 3 + 2] = 0;
                    }
                }
                else if (sharpening[m] > 255) {
                    if (m == 0) {
                        sharpening_image.data[i * image.cols * 3 + j * 3] = 255;
                    }
                    else if (m == 1) {
                        sharpening_image.data[i * image.cols * 3 + j * 3 + 1] = 255;
                    }
                    else if (m == 2) {
                        sharpening_image.data[i * image.cols * 3 + j * 3 + 2] = 255;
                    }
                }
                else {
                    if (m == 0) {
                        sharpening_image.data[i * image.cols * 3 + j * 3] = sharpening[m];
                    }
                    else if (m == 1) {
                        sharpening_image.data[i * image.cols * 3 + j * 3 + 1] = sharpening[m];
                    }
                    else if (m == 2) {
                        sharpening_image.data[i * image.cols * 3 + j * 3 + 2] = sharpening[m];
                    }
                }
            }
            x = 0, y = 0, z = 0;

        }
    }
    imshow("RGB Sharpening image", sharpening_image);

    return sharpening_image;
}

int main() {
    Mat image, G_image;
    image = imread("Lena.png");
    cvtColor(image, G_image, COLOR_BGR2GRAY);
    Mat G_average_image(G_image.rows, G_image.cols, CV_8UC1, Scalar(0));
    Mat RGB_average_image(G_image.rows, G_image.cols, CV_8UC1, Scalar(0));
    Mat filter(3, 3, CV_8UC1, Scalar(0));
    
    cout << "원하는 작업을 선택해 주세요 1.3x3 Moving_Average 2.Laplapician 3.Sharpening Filter" << "\n";
    /*int n;
    cin >> n;
    switch (n) {
    case 1:
        G_Moving_average(G_image, n);
        RGB_Moving_average(image, n);
    }*/
    
    /*G_Moving_average(G_image, n);
    RGB_Moving_average(image, n);*/
    RGB_Laplacian(image, 1);
    G_Laplacian(G_image, 1);
    G_Sharpening(G_image, 1);
    RGB_Sharpening(image, 1);

    imshow("image", image);
    imshow("Gray image", G_image);

    waitKey(0);
    return 0;
}

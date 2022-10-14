#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

Mat G_filtering(Mat image, int n,int row, int col) {
    unsigned char* pData = (unsigned char*)image.data; //받아온 이미지의 정보를 읽을 수 있도록 저장하는 공간
    int size = 2 * n + 1;
    int l = 0,c=0;
    int* count = new int[image.cols](); //값이 있는 값의 위치 정보를 담을 공간
    Mat filter(2*n+1, 2 * n + 1, CV_8UC1, Scalar(0)); //filtering하여 반환할 Mat

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
    Mat filter(2 * n + 1, 2 * n + 1, CV_8UC3, Scalar(0)); //gray와 다르게 CV_8UC3로 만들어 줍니다

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
            filter = G_filtering(G_image, n, j, i);//필터링 한 3x3값의 Mat을 받아옵니다.
            int sum = 0;
            for (int k = 0; k < size; k++) {
                sum += filter.data[k]; //모든 값을 더해줍니다.
            }
            average_image.data[i * G_image.cols + j] = sum / size;//평균을 구해 average_image에 넣어줍니다.
        }
    }
    imshow("Gray Moving Average image", average_image);

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
                    b_sum += (int)filter.data[k]; //Blue에 대한 색정보를 모두 더합니다
                }
                else if (k % 3 == 1) {
                    g_sum += (int)filter.data[k]; //Green에 대한 색정보를 모두 더합니다
                }
                else if (k % 3 == 2) {
                    r_sum += (int)filter.data[k]; //Red에 대한 색정보를 모두 더합니다
                }
            }
            
            //각각의 평균을 구합니다.
            average_image.data[i * image.cols *3 + j*3] = b_sum / (size);
            average_image.data[i * image.cols * 3 + j * 3 +1] = g_sum / (size );
            average_image.data[i * image.cols * 3 + j * 3 +2] = r_sum / (size );

        }
    }
    imshow("RGB Moving Average image", average_image);

    return average_image;
}

Mat G_Laplacian(Mat G_image, int n) {
    Mat laplacian_image(G_image.rows, G_image.cols, CV_8UC1, Scalar(0));
    Mat filter(2 * n + 1, 2 * n + 1, CV_8UC1, Scalar(0));
    int size = (2 * n + 1) * (2 * n + 1);
    for (int i = 0; i < G_image.rows; i++) {
        for (int j = 0; j < G_image.cols; j++) {
            filter = G_filtering(G_image, n, j, i);  
            int lap= (int)filter.data[1] + (int)filter.data[3] + (int)filter.data[5] + (int)filter.data[7] - (4 * (int)filter.data[4]); 
            //1,3,5,7값에는 1을 곱하여 더하고 4번째 픽셀 값에는 -4를 곱하여 더해줍니다
          
            if (lap < 0) {
                laplacian_image.data[i * G_image.cols + j] = 0; //0보다 작은 경우 0을 넣어줍니다.
            }
            else if (lap >255) {
                laplacian_image.data[i * G_image.cols + j] = 255; //255보다 큰 경우 255를 넣어줍니다.
            }
            else {
                laplacian_image.data[i * G_image.cols + j] = lap;
            }

        }
      
    }
    imshow("Gray Laplacian image", laplacian_image);

    return laplacian_image;
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
            else if (b > 255) {
                laplacian_image.data[i * image.cols * 3 + j * 3] = 255;
            }
            else {
                laplacian_image.data[i * image.cols * 3 + j * 3] = b;
            }
            if (g < 0) {
                laplacian_image.data[i * image.cols * 3 + j * 3+1] = 0;
            }
            else if (g > 255) {
                laplacian_image.data[i * image.cols * 3 + j * 3+1] = 255;
            }
            else {
                laplacian_image.data[i * image.cols * 3 + j * 3+1] = g;
            }
            if (r < 0) {
                laplacian_image.data[i * image.cols * 3 + j * 3+2] = 0;
            }
            else if (r > 255) {
                laplacian_image.data[i * image.cols * 3 + j * 3+2] = 255;
            }
            else {
                laplacian_image.data[i * image.cols * 3 + j * 3+2] = r;
            }
            

            x = 0, y = 0, z = 0;

        }
    }
    imshow("RGB Laplacian image", laplacian_image);

    return laplacian_image;
}

Mat G_Sharpening(Mat G_image, int n) {
    Mat sharpening_image(G_image.rows, G_image.cols, CV_8UC1, Scalar(0));
    Mat filter(2 * n + 1, 2 * n + 1, CV_8UC1, Scalar(0));
    int size = (2 * n + 1) * (2 * n + 1);
    for (int i = 0; i < G_image.rows; i++) {
        for (int j = 0; j < G_image.cols; j++) {
            filter = G_filtering(G_image, n, j, i);
          
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
    int* sharpening = new int[3](); //RGB의 값을 각각 넣을 공간
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
    
    cout << "원하는 작업을 선택해 주세요 1.3x3 Moving_Average 2.Laplapician 3.Sharpening Filter 4.all" << "\n";
    int n;
    cin >> n;
    switch (n) {
    case 1:
        G_Moving_average(G_image, 1);
        RGB_Moving_average(image, 1);
        moveWindow("Gray Moving Average image", 400, 500);
        moveWindow("RGB Moving Average image",400, 100);
        break;
    case 2:
        G_Laplacian(G_image, 1);
        RGB_Laplacian(image, 1);
        moveWindow("Gray Laplacian image", 400, 500);
        moveWindow("RGB Laplacian image", 400, 100);
        break;
    case 3:
        G_Sharpening(G_image, 1);
        RGB_Sharpening(image, 1);
        moveWindow("Gray Sharpening image", 400, 500);
        moveWindow("RGB Sharpening image", 400, 100);
        break;
    case 4:
        G_Moving_average(G_image, 1);
        RGB_Moving_average(image, 1);
        RGB_Laplacian(image, 1);
        G_Laplacian(G_image, 1);
        G_Sharpening(G_image, 1);
        RGB_Sharpening(image, 1);
        moveWindow("Gray Moving Average image", 400, 500);
        moveWindow("RGB Moving Average image", 400, 100);
        moveWindow("Gray Laplacian image", 700, 500);
        moveWindow("RGB Laplacian image", 700, 100);
        moveWindow("Gray Sharpening image", 1000, 500);
        moveWindow("RGB Sharpening image", 1000, 100);
        break;
    }
    
    

    imshow("image", image);
    imshow("Gray image", G_image);
    moveWindow("image", 100, 100);
    moveWindow("Gray image", 100, 500);

    waitKey(0);
    return 0;
}

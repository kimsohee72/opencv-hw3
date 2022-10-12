#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int* filtering(Mat image, int n,int row, int col) {
    unsigned char* pData = (unsigned char*)image.data;
    int size = 2 * n + 1;
    int l = 0,c=0;
    int* count = new int[image.rows]();
    int* filter = new int[size * size]();
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
        if (row + k >= 0 && row + k < image.rows) {
            count[l] = k;
            l++;
        }
    }

    
    for (int k = -n; k <= n; k++) {
        if (col + k >= 0 && col + k < image.cols) {
            if (l <  size && row - count[0] + 1 >= image.rows) {
                for (int h = 0; h < l; h++) {
                    filter[c] = row + image.rows * k + count[h] + image.rows * col;
                    c++;
                }
                for (int h = 0; h < size - l; h++) {
                    filter[c] = 0;
                    c++;
                }
            }
            else if (l < size && row + count[0] - 1 < 0) {
                for (int h = 0; h < size - l; h++) {
                    filter[c] = 0;
                    c++;
                }
                for (int h = 0; h < l; h++) {
                    filter[c] = row + image.rows * k + count[h] + image.rows * col;
                    c++;
                }
            }
            else {
                for (int h = 0; h < l; h++) {
                    filter[c] = row + image.rows * k + count[h] + image.rows * col;
                    c++;
                }
            }
        }
        else {
            for (int p = 0; p < size; p++) {
                filter[c] = 0;
                c++;
            }
        }
    }

    return filter;
}

int main() {
    Mat image, image_YUV;
    image = imread("p.png");
 
    /*imshow("image", image);*/
    int n;

    cin >> n;
    
    int* count = filtering(image, n, 0, 0);
    for (int i = 0; i < (2*n+1)*(2*n+1); i++) {
        cout << count[i] << " ";
        if (i % (2*n+1) == 2 * n ) {
            cout << "\n";
        }
    }
       

    waitKey(0);
    return 0;
}

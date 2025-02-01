#include <bits/stdc++.h>

using namespace std;

int gcd(int a, int b) {
    if(b == 0) return a;
    return gcd(b, a % b);
}

class Matrix {
    private: 
        int n, m;
        vector<vector<int> > mat;
    public: 
        Matrix() {
            
        }

        void read() {
            cout << "Enter dimensions (n, m): ";
            cin >> n >> m;
            mat.clear();
            mat.resize(n, vector<int> (m));
            cout << "Enter matrix entries:\n";
            for(int i = 0; i < n; i++) {
                for(int j = 0; j < m; j++) {
                    cin >> mat[i][j];
                }
            }
        }

        void multiply_row(vector<int>& row, int x) {
            for(int &val : row) 
                val *= x;
        }

        void subtract_row(vector<int>& row1, vector<int>& row2) {
            for(int i = 0; i < m; i++) {
                row1[i] -= row2[i];
            }
        }

        void reduce_row(vector<int>& row) {
            int g = 0;
            for(int j = 0; j < m; j++)
                g = gcd(g, row[j]);
            
            for(int j = 0; j < m; j++)
                row[j] = row[j] / g;   
        }

        void sort_by_row_entry(vector<vector<int> >& rrefmat, int i) {
            sort(rrefmat.begin(), rrefmat.end(), [&](vector<int> row1, vector<int> row2) {
                return row1[i] > row2[i];
            });
        }

        void print() {
            for(auto row : mat) {
                for(int x : row) {
                    cout << setw(4) << x << " ";
                }
                cout << "\n";
            }
        }

        int leading_entry(vector<int>& row) {
            int i = 0;
            while(i < m && !row[i]) {
                i++;
            }
            return i;
        }

        void format(vector<vector<int> >& matrix) {
            sort(matrix.begin(), matrix.end(), [&](vector<int>& row1, vector<int>& row2) {
                return leading_entry(row1) < leading_entry(row2);
            });
        }

        void transpose() {
            vector<vector<int> > transposed_mat(m, vector<int> (n));
            for(int i = 0; i < n; i++) {
                for(int j = 0; j < m; j++) {
                    transposed_mat[j][i] = mat[i][j];
                }
            }
            swap(n, m);
            mat = transposed_mat;
        }

        void rref() {
            auto rrefmat = mat;

            // reduce every row
            for(int i = 0; i < n; i++) {
                reduce_row(rrefmat[i]);
            }

            for(int i = 0; i < m; i++) {
                // for each col.

                bool willprocess = false;
                for(int j = 0; j < n; j++) {
                    // i-th entry is not zero and pre are 0.
                    if(!rrefmat[j][i]) continue;
                    bool has_entry = false;
                    for(int k = 0; k < i; k++) {
                        if(rrefmat[j][k] != 0) {
                            has_entry = true;
                            break;
                        }
                    }
                    if(!has_entry) {
                        swap(rrefmat[0], rrefmat[j]);
                        willprocess = true;
                        break;
                    }
                }

                if(!willprocess) {
                    continue;
                }

                for(auto row : rrefmat) {
                    for(int x : row) {
                        cout << setw(4) << x << " ";
                    }
                    cout << "\n";
                }
                cout << "\n\n";

                for(int j = 1; j < n; j++) {
                    if(rrefmat[j][i] == 0) continue;

                    int lcm = rrefmat[j][i] * rrefmat[0][i] / gcd(rrefmat[j][i], rrefmat[0][i]);
                    int multiple1 = lcm / rrefmat[0][i], multiple2 = lcm / rrefmat[j][i];
                    multiply_row(rrefmat[0], multiple1);
                    multiply_row(rrefmat[j], multiple2);
                    subtract_row(rrefmat[j], rrefmat[0]);
                    reduce_row(rrefmat[0]);
                    reduce_row(rrefmat[j]);
                }
            }

            format(rrefmat);
            cout << "rref:\n";
            for(int i = 0; i < n; i++) {
                int lead_ind = leading_entry(rrefmat[i]);
                int entry = rrefmat[i][lead_ind];
                for(int j = 0; j < m; j++) {
                    if(rrefmat[i][j] % entry == 0) {
                        cout << setw(6) << rrefmat[i][j] / entry << " ";
                    } else {
                        int g = gcd(rrefmat[i][j], entry);
                        rrefmat[i][j] /= g;
                        cout << setw(6) << rrefmat[i][j] << "/" << entry / g << " ";
                    }
                }
                cout << "\n";
            }
        }
};

int main() {
    Matrix mat;
    string instructions = "1. Enter the matrix\n2. Row reduced echelon\n3. Transpose\n4. Print Matrix\n5. Exit\n\n";
    while(true) {
        cout << instructions;
        int operation;
        cin >> operation;
        switch (operation)
        {
        case 1:
            mat.read();
            break;
        case 2:
            mat.rref();
            break;

        case 3: 
            mat.transpose();
            break;

        case 4: 
            mat.print();
            break;
        case 5: 
            return 0;
        default:
            cout << "No operation\n";
            break;
        }
    }


    return 0;
}

/* stuff you should look for
    * int overflow, array bounds
    * special cases (n=1?)
    * do smth instead of nothing and stay organized
    * WRITE STUFF DOWN
    * DON'T GET STUCK ON ONE APPROACH
*/


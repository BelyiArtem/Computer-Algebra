// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <complex>
#include <math.h>
#include <algorithm> 
#include <iostream>
#include <ostream>
#define _USE_MATH_DEFINES
#define M_PI           3.14159265358979323846  /* pi */
const int mod = 7340033;
const int root = 5;
const int root_1 = 4404020;
const int root_pw = 1 << 20;

using namespace std;
typedef complex<double> base;


void fftr(vector<int> & a, bool invert) {
	int n = (int)a.size();

	for (int i = 1, j = 0; i<n; ++i) {
		int bit = n >> 1;
		for (; j >= bit; bit >>= 1)
			j -= bit;
		j += bit;
		if (i < j)
			swap(a[i], a[j]);
	}

	for (int len = 2; len <= n; len <<= 1) {
		int wlen = invert ? root_1 : root;
		for (int i = len; i<root_pw; i <<= 1)
			wlen = int(wlen * 1ll * wlen % mod);
		for (int i = 0; i<n; i += len) {
			int w = 1;
			for (int j = 0; j<len / 2; ++j) {
				int u = a[i + j], v = int(a[i + j + len / 2] * 1ll * w % mod);
				a[i + j] = u + v < mod ? u + v : u + v - mod;
				a[i + j + len / 2] = u - v >= 0 ? u - v : u - v + mod;
				w = int(w * 1ll * wlen % mod);
			}
		}
	}
	if (invert) {
		int nrev = reverse(a.size(), mod);
		for (int i = 0; i<n; ++i)
			a[i] = int(a[i] * 1ll * nrev % mod);
	}
}


void fft(vector<base> & a, bool invert){
	int n = (int)a.size();
	if (n == 1)  return;

	vector<base> a0(n / 2), a1(n / 2);
	for (int i = 0, j = 0; i<n; i += 2, ++j) {
		a0[j] = a[i];
		a1[j] = a[i + 1];
	}
	fft(a0, invert);
	fft(a1, invert);

	double ang = 2 * M_PI / n * (invert ? -1 : 1);
	base w(1), wn(cos(ang), sin(ang));
	for (int i = 0; i<n / 2; ++i) {
		a[i] = a0[i] + w * a1[i];
		a[i + n / 2] = a0[i] - w * a1[i];
		if (invert)
			a[i] /= 2, a[i + n / 2] /= 2;
		w *= wn;
	}
}

void multiply(const vector<int> & a, const vector<int> & b, vector<int> & res) {
	vector<base> fa(a.begin(), a.end()), fb(b.begin(), b.end());
	size_t n = 1;
	while (n < max(a.size(), b.size()))  n <<= 1;
	n <<= 1;
	fa.resize(n), fb.resize(n);

	fft(fa, false), fft(fb, false);
	for (size_t i = 0; i<n; ++i)
		fa[i] *= fb[i];
	fft(fa, true);

	res.resize(n);
	for (size_t i = 0; i<n; ++i)
		res[i] = int(fa[i].real() + 0.5);
}


int main()
{	
	vector<base> a(2,3);
	fft(a, 0);
	cout << fft;
	getchar();
    return 0;
}


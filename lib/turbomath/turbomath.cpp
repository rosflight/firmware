/*
 *
 * BSD 3-Clause License
 *
 * Copyright (c) 2017, James Jackson - BYU MAGICC Lab, Provo UT
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <turbomath/turbomath.h>

namespace turbomath
{

vector::vector()
{
  x = 0.0f;
  y = 0.0f;
  z = 0.0f;
}

vector::vector(float x_, float y_, float z_)
{
  x = x_;
  y = y_;
  z = z_;
}


float vector::norm() const
{
  return 1.0/inv_sqrt(x*x + y*y + z*z);
}


float vector::sqrd_norm() const
{
  return x*x + y*y + z*z;
}


vector& vector::normalize()
{
  float recip_norm = inv_sqrt(x*x + y*y + z*z);
  x *= recip_norm;
  y *= recip_norm;
  z *= recip_norm;
  return *this;
}


vector vector::normalized() const
{
  float recip_norm = inv_sqrt(x*x + y*y + z*z);
  vector out(x * recip_norm, y*recip_norm, z*recip_norm);
  return out;
}


vector vector::operator+(const vector v) const
{
  vector out(x + v.x, y + v.y, z + v.z);
  return out;
}


vector vector::operator-(const vector v) const
{
  vector out(x - v.x, y - v.y, z - v.z);
  return out;
}


vector& vector::operator +=(const vector v)
{
  x += v.x;
  y += v.y;
  z += v.z;
  return *this;
}


vector& vector::operator -=(const vector v)
{
  x -= v.x;
  y -= v.y;
  z -= v.z;
  return *this;
}


vector vector::operator *(const float s) const
{
  vector out(x*s, y*s, z*s);
  return out;
}


vector vector::operator /(const float s) const
{
  vector out(x/s, y/s, z/s);
  return out;
}


vector& vector::operator *=(const float s)
{
  x *= s;
  y *= s;
  z *= s;
  return *this;
}


vector& vector::operator /=(const float s)
{
  x /= s;
  y /= s;
  z /= s;
  return *this;
}


float vector::dot(const vector v) const
{
  return x*v.x + y*v.y + z*v.z;
}


vector vector::cross(const vector v) const
{
  vector out( y * v.z - z * v.y,
                     z * v.x - x * v.z,
                     x * v.y - y * v.x);
  return out;
}

quaternion::quaternion()
{
  w = 1.0f;
  x = 0.0f;
  y = 0.0f;
  z = 0.0f;
}

quaternion::quaternion(float w_, float x_, float y_, float z_)
{
  w = w_;
  x = x_;
  y = y_;
  z = z_;
}

quaternion::quaternion(const vector u, const vector v)
{
  from_two_unit_vectors(u, v);
}

quaternion& quaternion::normalize()
{
  float recip_norm = inv_sqrt(w*w + x*x + y*y + z*z);
  w *= recip_norm;
  x *= recip_norm;
  y *= recip_norm;
  z *= recip_norm;
  return *this;
}

quaternion quaternion::operator *(const quaternion q) const
{
  quaternion q_out(w*q.w - x*q.x - y*q.y - z*q.z,
                   w*q.x + x*q.w - y*q.z + z*q.y,
                   w*q.y + x*q.z + y*q.w - z*q.x,
                   w*q.z - x*q.y + y*q.x + z*q.w);
  return q_out;
}

quaternion& quaternion::operator *=(const quaternion q)
{
  quaternion q_out(w*q.w - x*q.x - y*q.y - z*q.z,
                   w*q.x + x*q.w - y*q.z + z*q.y,
                   w*q.y + x*q.z + y*q.w - z*q.x,
                   w*q.z - x*q.y + y*q.x + z*q.w);
  w = q_out.w;
  x = q_out.x;
  y = q_out.y;
  z = q_out.z;
  return *this;
}

vector quaternion::rotate(const vector v) const
{
    vector out((1.0f - 2.0f*y*y - 2.0f*z*z) * v.x + (2.0f*(x*y + w*z))*v.y + 2.0f*(x*z - w*y)*v.z,
               (2.0f*(x*y - w*z)) * v.x + (1.0f - 2.0f*x*x - 2.0f*z*z) * v.y + 2.0f*(y*z + w*x)*v.z,
               (2.0f*(x*z + w*y)) * v.x + 2.0f*(y*z - w*x)*v.y + (1.0f - 2.0f*x*x - 2.0f*y*y)*v.z);
    return out;
}

vector quaternion::operator *(const vector v) const
{
    vector out((1.0f - 2.0f*y*y - 2.0f*z*z) * v.x + (2.0f*(x*y + w*z))*v.y + 2.0f*(x*z - w*y)*v.z,
               (2.0f*(x*y - w*z)) * v.x + (1.0f - 2.0f*x*x - 2.0f*z*z) * v.y + 2.0f*(y*z + w*x)*v.z,
               (2.0f*(x*z + w*y)) * v.x + 2.0f*(y*z - w*x)*v.y + (1.0f - 2.0f*x*x - 2.0f*y*y)*v.z);
    return out;
}

quaternion quaternion::inverse() const
{
  quaternion out(w, -x, -y, -z);
  return out;
}

quaternion& quaternion::invert()
{
  x *= -1.0f;
  y *= -1.0f;
  z *= -1.0f;
  return *this;
}

quaternion& quaternion::from_two_unit_vectors(const vector u, const vector v)
{
  // Adapted From the Ogre3d source code
  // https://bitbucket.org/sinbad/ogre/src/9db75e3ba05c/OgreMain/include/OgreVector3.h?fileviewer=file-view-default#cl-651
  float d = u.dot(v);
  if ( d >= 1.0f)
  {
    w = 1.0f;
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
    return *this;
  }
  else
  {
    float invs = inv_sqrt(2.0f*(1.0f+d));
    vector xyz = u.cross(v)*invs;
    w = 0.5f/invs;
    x = xyz.x;
    y = xyz.y;
    z = xyz.z;
  }
  normalize();
  return *this;
}

void quaternion::get_RPY(float& roll, float& pitch, float& yaw) const
{
  roll = turbomath::atan2(2.0f * (w*x + y*z), 1.0f - 2.0f * (x*x + y*y));
  pitch = turbomath::asin(2.0f*(w*y - z*x));
  yaw = turbomath::atan2(2.0f * (w*z + x*y), 1.0f - 2.0f * (y*y + z*z));
}



} // namespace turbomath

namespace turbo = turbomath;

#ifndef M_PI
#define M_PI 3.14159265359
#endif

static const float atan_max_x = 1.000000;
static const float atan_min_x = 0.000000;
static const int16_t atan_num_entries = 500;
static const float atan_scale_factor = 10000.000000;
static const int16_t atan_lookup_table[500] = {
0,	20,	40,	60,	80,	100,	120,	140,	160,	180,
200,	220,	240,	260,	280,	300,	320,	340,	360,	380,
400,	420,	440,	460,	480,	500,	520,	539,	559,	579,
599,	619,	639,	659,	679,	699,	719,	739,	759,	778,
798,	818,	838,	858,	878,	898,	917,	937,	957,	977,
997,	1016,	1036,	1056,	1076,	1096,	1115,	1135,	1155,	1175,
1194,	1214,	1234,	1253,	1273,	1293,	1312,	1332,	1352,	1371,
1391,	1411,	1430,	1450,	1469,	1489,	1508,	1528,	1548,	1567,
1587,	1606,	1626,	1645,	1664,	1684,	1703,	1723,	1742,	1762,
1781,	1800,	1820,	1839,	1858,	1878,	1897,	1916,	1935,	1955,
1974,	1993,	2012,	2032,	2051,	2070,	2089,	2108,	2127,	2146,
2166,	2185,	2204,	2223,	2242,	2261,	2280,	2299,	2318,	2337,
2355,	2374,	2393,	2412,	2431,	2450,	2469,	2487,	2506,	2525,
2544,	2562,	2581,	2600,	2618,	2637,	2656,	2674,	2693,	2712,
2730,	2749,	2767,	2786,	2804,	2823,	2841,	2859,	2878,	2896,
2915,	2933,	2951,	2970,	2988,	3006,	3024,	3043,	3061,	3079,
3097,	3115,	3133,	3151,	3169,	3187,	3206,	3224,	3241,	3259,
3277,	3295,	3313,	3331,	3349,	3367,	3385,	3402,	3420,	3438,
3456,	3473,	3491,	3509,	3526,	3544,	3561,	3579,	3596,	3614,
3631,	3649,	3666,	3684,	3701,	3719,	3736,	3753,	3771,	3788,
3805,	3822,	3839,	3857,	3874,	3891,	3908,	3925,	3942,	3959,
3976,	3993,	4010,	4027,	4044,	4061,	4078,	4095,	4112,	4128,
4145,	4162,	4179,	4195,	4212,	4229,	4245,	4262,	4278,	4295,
4311,	4328,	4344,	4361,	4377,	4394,	4410,	4426,	4443,	4459,
4475,	4491,	4508,	4524,	4540,	4556,	4572,	4588,	4604,	4620,
4636,	4652,	4668,	4684,	4700,	4716,	4732,	4748,	4764,	4779,
4795,	4811,	4827,	4842,	4858,	4874,	4889,	4905,	4920,	4936,
4951,	4967,	4982,	4998,	5013,	5028,	5044,	5059,	5074,	5090,
5105,	5120,	5135,	5150,	5166,	5181,	5196,	5211,	5226,	5241,
5256,	5271,	5286,	5301,	5315,	5330,	5345,	5360,	5375,	5389,
5404,	5419,	5434,	5448,	5463,	5477,	5492,	5507,	5521,	5535,
5550,	5564,	5579,	5593,	5608,	5622,	5636,	5650,	5665,	5679,
5693,	5707,	5721,	5736,	5750,	5764,	5778,	5792,	5806,	5820,
5834,	5848,	5862,	5875,	5889,	5903,	5917,	5931,	5944,	5958,
5972,	5985,	5999,	6013,	6026,	6040,	6053,	6067,	6080,	6094,
6107,	6121,	6134,	6147,	6161,	6174,	6187,	6201,	6214,	6227,
6240,	6253,	6267,	6280,	6293,	6306,	6319,	6332,	6345,	6358,
6371,	6384,	6397,	6409,	6422,	6435,	6448,	6461,	6473,	6486,
6499,	6511,	6524,	6537,	6549,	6562,	6574,	6587,	6599,	6612,
6624,	6637,	6649,	6661,	6674,	6686,	6698,	6711,	6723,	6735,
6747,	6760,	6772,	6784,	6796,	6808,	6820,	6832,	6844,	6856,
6868,	6880,	6892,	6904,	6916,	6928,	6940,	6951,	6963,	6975,
6987,	6998,	7010,	7022,	7033,	7045,	7057,	7068,	7080,	7091,
7103,	7114,	7126,	7137,	7149,	7160,	7171,	7183,	7194,	7205,
7217,	7228,	7239,	7250,	7261,	7273,	7284,	7295,	7306,	7317,
7328,	7339,	7350,	7361,	7372,	7383,	7394,	7405,	7416,	7427,
7438,	7448,	7459,	7470,	7481,	7491,	7502,	7513,	7524,	7534,
7545,	7555,	7566,	7577,	7587,	7598,	7608,	7619,	7629,	7640,
7650,	7660,	7671,	7681,	7691,	7702,	7712,	7722,	7733,	7743,
7753,	7763,	7773,	7783,	7794,	7804,	7814,	7824,	7834,	7844,
};

static const float asin_max_x = 1.000000;
static const float asin_min_x = 0.000000;
static const int16_t asin_num_entries = 500;
static const float asin_scale_factor = 10000.000000;
static const int16_t asin_lookup_table[501] = {
0,	20,	40,	60,	80,	100,	120,	140,	160,	180,
200,	220,	240,	260,	280,	300,	320,	340,	360,	380,
400,	420,	440,	460,	480,	500,	520,	540,	560,	580,
600,	620,	640,	660,	681,	701,	721,	741,	761,	781,
801,	821,	841,	861,	881,	901,	921,	941,	961,	982,
1002,	1022,	1042,	1062,	1082,	1102,	1122,	1142,	1163,	1183,
1203,	1223,	1243,	1263,	1284,	1304,	1324,	1344,	1364,	1384,
1405,	1425,	1445,	1465,	1485,	1506,	1526,	1546,	1566,	1587,
1607,	1627,	1647,	1668,	1688,	1708,	1729,	1749,	1769,	1790,
1810,	1830,	1851,	1871,	1891,	1912,	1932,	1952,	1973,	1993,
2014,	2034,	2054,	2075,	2095,	2116,	2136,	2157,	2177,	2198,
2218,	2239,	2259,	2280,	2300,	2321,	2341,	2362,	2382,	2403,
2424,	2444,	2465,	2486,	2506,	2527,	2547,	2568,	2589,	2610,
2630,	2651,	2672,	2692,	2713,	2734,	2755,	2775,	2796,	2817,
2838,	2859,	2880,	2900,	2921,	2942,	2963,	2984,	3005,	3026,
3047,	3068,	3089,	3110,	3131,	3152,	3173,	3194,	3215,	3236,
3257,	3278,	3300,	3321,	3342,	3363,	3384,	3405,	3427,	3448,
3469,	3490,	3512,	3533,	3554,	3576,	3597,	3618,	3640,	3661,
3683,	3704,	3726,	3747,	3769,	3790,	3812,	3833,	3855,	3876,
3898,	3920,	3941,	3963,	3985,	4006,	4028,	4050,	4072,	4093,
4115,	4137,	4159,	4181,	4203,	4225,	4246,	4268,	4290,	4312,
4334,	4357,	4379,	4401,	4423,	4445,	4467,	4489,	4511,	4534,
4556,	4578,	4601,	4623,	4645,	4668,	4690,	4712,	4735,	4757,
4780,	4802,	4825,	4848,	4870,	4893,	4916,	4938,	4961,	4984,
5007,	5029,	5052,	5075,	5098,	5121,	5144,	5167,	5190,	5213,
5236,	5259,	5282,	5305,	5329,	5352,	5375,	5398,	5422,	5445,
5469,	5492,	5515,	5539,	5562,	5586,	5610,	5633,	5657,	5681,
5704,	5728,	5752,	5776,	5800,	5824,	5848,	5872,	5896,	5920,
5944,	5968,	5992,	6016,	6041,	6065,	6089,	6114,	6138,	6163,
6187,	6212,	6236,	6261,	6286,	6311,	6335,	6360,	6385,	6410,
6435,	6460,	6485,	6510,	6535,	6561,	6586,	6611,	6637,	6662,
6687,	6713,	6739,	6764,	6790,	6816,	6841,	6867,	6893,	6919,
6945,	6971,	6997,	7023,	7050,	7076,	7102,	7129,	7155,	7182,
7208,	7235,	7262,	7288,	7315,	7342,	7369,	7396,	7423,	7450,
7478,	7505,	7532,	7560,	7587,	7615,	7643,	7670,	7698,	7726,
7754,	7782,	7810,	7838,	7867,	7895,	7923,	7952,	7981,	8009,
8038,	8067,	8096,	8125,	8154,	8183,	8213,	8242,	8271,	8301,
8331,	8360,	8390,	8420,	8450,	8481,	8511,	8541,	8572,	8602,
8633,	8664,	8695,	8726,	8757,	8788,	8820,	8851,	8883,	8915,
8947,	8979,	9011,	9043,	9076,	9108,	9141,	9174,	9207,	9240,
9273,	9306,	9340,	9374,	9407,	9442,	9476,	9510,	9545,	9579,
9614,	9649,	9684,	9720,	9755,	9791,	9827,	9863,	9900,	9936,
9973,	10010,	10047,	10084,	10122,	10160,	10198,	10236,	10275,	10314,
10353,	10392,	10432,	10471,	10512,	10552,	10593,	10634,	10675,	10717,
10759,	10801,	10844,	10886,	10930,	10973,	11018,	11062,	11107,	11152,
11198,	11244,	11290,	11337,	11385,	11433,	11481,	11530,	11580,	11630,
11681,	11732,	11784,	11837,	11890,	11944,	11999,	12054,	12111,	12168,
12226,	12285,	12346,	12407,	12469,	12532,	12597,	12663,	12730,	12799,
12870,	12942,	13017,	13093,	13171,	13252,	13336,	13423,	13513,	13606,
13705,	13808,	13917,	14033,	14157,	14293,	14442,	14612,	14813,	15075,
15708
};

static const int32_t max_pressure = 106598;
static const int32_t min_pressure = 69681;
static const int16_t num_entries = 500;
static const int16_t dx = 73;
static const int16_t alt_lookup_table[500] = {
30467,  30384,  30301,  30218,  30135,  30052,  29970,  29887,  29804,  29722,
29639,  29557,  29474,  29392,  29310,  29227,  29145,  29063,  28981,  28899,
28818,  28736,  28654,  28573,  28491,  28410,  28328,  28247,  28166,  28084,
28003,  27922,  27841,  27760,  27679,  27598,  27518,  27437,  27356,  27276,
27195,  27115,  27035,  26954,  26874,  26794,  26714,  26634,  26554,  26474,
26394,  26315,  26235,  26155,  26076,  25996,  25917,  25837,  25758,  25679,
25600,  25521,  25442,  25363,  25284,  25205,  25126,  25047,  24969,  24890,
24811,  24733,  24655,  24576,  24498,  24420,  24341,  24263,  24185,  24107,
24029,  23952,  23874,  23796,  23718,  23641,  23563,  23486,  23408,  23331,
23254,  23176,  23099,  23022,  22945,  22868,  22791,  22714,  22637,  22561,
22484,  22407,  22331,  22254,  22178,  22101,  22025,  21949,  21872,  21796,
21720,  21644,  21568,  21492,  21416,  21340,  21265,  21189,  21113,  21038,
20962,  20887,  20811,  20736,  20661,  20585,  20510,  20435,  20360,  20285,
20210,  20135,  20060,  19985,  19911,  19836,  19761,  19687,  19612,  19538,
19463,  19389,  19315,  19240,  19166,  19092,  19018,  18944,  18870,  18796,
18722,  18649,  18575,  18501,  18427,  18354,  18280,  18207,  18133,  18060,
17987,  17914,  17840,  17767,  17694,  17621,  17548,  17475,  17402,  17329,
17257,  17184,  17111,  17039,  16966,  16894,  16821,  16749,  16676,  16604,
16532,  16460,  16387,  16315,  16243,  16171,  16099,  16027,  15956,  15884,
15812,  15740,  15669,  15597,  15526,  15454,  15383,  15311,  15240,  15169,
15098,  15026,  14955,  14884,  14813,  14742,  14671,  14600,  14530,  14459,
14388,  14317,  14247,  14176,  14106,  14035,  13965,  13894,  13824,  13754,
13684,  13613,  13543,  13473,  13403,  13333,  13263,  13193,  13123,  13054,
12984,  12914,  12845,  12775,  12705,  12636,  12566,  12497,  12428,  12358,
12289,  12220,  12151,  12081,  12012,  11943,  11874,  11805,  11737,  11668,
11599,  11530,  11461,  11393,  11324,  11256,  11187,  11119,  11050,  10982,
10913,  10845,  10777,  10709,  10641,  10572,  10504,  10436,  10368,  10300,
10233,  10165,  10097,  10029,  9962,   9894,   9826,   9759,   9691,   9624,
9556,   9489,   9422,   9354,   9287,   9220,   9153,   9086,   9018,   8951,
8884,   8817,   8751,   8684,   8617,   8550,   8483,   8417,   8350,   8283,
8217,   8150,   8084,   8018,   7951,   7885,   7819,   7752,   7686,   7620,
7554,   7488,   7422,   7356,   7290,   7224,   7158,   7092,   7026,   6961,
6895,   6829,   6764,   6698,   6633,   6567,   6502,   6436,   6371,   6306,
6240,   6175,   6110,   6045,   5980,   5915,   5849,   5784,   5720,   5655,
5590,   5525,   5460,   5395,   5331,   5266,   5201,   5137,   5072,   5008,
4943,   4879,   4815,   4750,   4686,   4622,   4557,   4493,   4429,   4365,
4301,   4237,   4173,   4109,   4045,   3981,   3917,   3854,   3790,   3726,
3663,   3599,   3535,   3472,   3408,   3345,   3281,   3218,   3155,   3091,
3028,   2965,   2902,   2838,   2775,   2712,   2649,   2586,   2523,   2460,
2397,   2335,   2272,   2209,   2146,   2084,   2021,   1958,   1896,   1833,
1771,   1708,   1646,   1583,   1521,   1459,   1396,   1334,   1272,   1210,
1148,   1085,   1023,   961,    899,    837,    776,    714,    652,    590,
528,    467,    405,    343,    282,    220,    158,    97,     35,     -26,
-87,    -149,   -210,   -271,   -333,   -394,   -455,   -516,   -577,   -638,
-699,   -760,   -821,   -882,   -943,   -1004,  -1065,  -1126,  -1186,  -1247,
-1308,  -1369,  -1429,  -1490,  -1550,  -1611,  -1671,  -1732,  -1792,  -1852,
-1913,  -1973,  -2033,  -2094,  -2154,  -2214,  -2274,  -2334,  -2394,  -2454,
-2514,  -2574,  -2634,  -2694,  -2754,  -2814,  -2874,  -2933,  -2993,  -3053,
-3112,  -3172,  -3232,  -3291,  -3351,  -3410,  -3469,  -3529,  -3588,  -3648,
-3707,  -3766,  -3825,  -3885,  -3944,  -4003,  -4062,  -4121,  -4180,  -4239
};

float turbo::fsign(float y)
{
  return (0.0f < y) - (y < 0.0f);
}


float turbo::atan(float x)
{
  // atan is symmetric
  if (x < 0)
  {
    return -1.0*turbo::atan(-1.0*x);
  }
  // This uses a sweet identity to wrap the domain of atan onto (0,1)
  if (x > 1.0)
  {
    return M_PI/2.0 - turbo::atan(1.0/x);
  }

  float t = (x - atan_min_x)/(atan_max_x - atan_min_x) * static_cast<float>(atan_num_entries);
  int16_t index = static_cast<int16_t>(t);
  float delta_x = t - index;

  if (index >= atan_num_entries)
      return atan_lookup_table[atan_num_entries-1]/atan_scale_factor;
  else if (index < atan_num_entries - 1)
      return atan_lookup_table[index]/atan_scale_factor + delta_x * (atan_lookup_table[index + 1] - atan_lookup_table[index])/atan_scale_factor;
  else
      return atan_lookup_table[index]/atan_scale_factor + delta_x * (atan_lookup_table[index] - atan_lookup_table[index - 1])/atan_scale_factor;
}


float turbo::atan2(float y, float x)
{
  // algorithm from wikipedia: https://en.wikipedia.org/wiki/Atan2
  if (x == 0.0)
  {
    if (y < 0.0)
    {
      return - M_PI/2.0;
    }
    else if ( y > 0.0)
    {
      return M_PI/2.0;
    }
    else
    {
      return 0.0;
    }
  }

  float arctan = turbo::atan(y/x);

  if (x < 0.0)
  {
    if ( y < 0)
    {
      return arctan - M_PI;
    }
    else
    {
      return arctan + M_PI;
    }
  }

  else
  {
      return arctan;
  }
}


float turbo::asin(float x)
{
  if (x < 0.0)
  {
    return -1.0*turbo::asin(-1.0*x);
  }

  float t = (x - asin_min_x)/(asin_max_x - asin_min_x) * static_cast<float>(asin_num_entries);
  int16_t index = static_cast<int16_t>(t);
  float delta_x = t - index;

  if (index >= asin_num_entries)
      return asin_lookup_table[500]/asin_scale_factor;
  else if (index < asin_num_entries - 1)
      return asin_lookup_table[index]/asin_scale_factor + delta_x * (asin_lookup_table[index + 1] - asin_lookup_table[index])/asin_scale_factor;
  else
      return asin_lookup_table[index]/asin_scale_factor + delta_x * (asin_lookup_table[index] - asin_lookup_table[index - 1])/asin_scale_factor;
}

float turbo::alt(float press)
{

  if(press < max_pressure && press > min_pressure)
  {
    float t = static_cast<float>(num_entries)*(press - static_cast<float>(min_pressure)) / static_cast<float>(max_pressure - min_pressure);
    int16_t index = static_cast<int16_t>(t);
    float dp = t - static_cast<float>(index);

    float out = 0.0;

    if (index < num_entries - 1)
    {
      out = alt_lookup_table[index]/10.0 + dp * (alt_lookup_table[index + 1] - alt_lookup_table[index])/10.0;
    }
    else
    {
      out = alt_lookup_table[index]/10.0 + dp * (alt_lookup_table[index] - alt_lookup_table[index - 1])/10.0;
    }

    return out;
  }
  else
    return 0.0;
}

float turbo::fabs(float x)
{
  if (x < 0)
    return -x;
  else
    return x;

}

float turbo::inv_sqrt(float x)
{
  volatile float x2;
  volatile turbo::float_converter_t y, i;
  const float threehalfs = 1.5F;

  x2 = x * 0.5F;
  y.fvalue  = x;
  i.ivalue  = y.ivalue;                             // evil floating point bit level hacking
  i.ivalue  = 0x5f3759df - (i.ivalue >> 1);
  y.fvalue = i.fvalue;
  y.fvalue  = y.fvalue * (threehalfs - (x2 * y.fvalue * y.fvalue));       // 1st iteration
  y.fvalue  = y.fvalue * (threehalfs - (x2 * y.fvalue * y.fvalue));       // 2nd iteration, this can be removed

  return turbo::fabs(y.fvalue);
}

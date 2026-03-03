#include "sha1.h"
#include <vector>
#include <sstream>
#include <iomanip>
#include <cstdint>
#include <sstream>
using namespace std;

class SHA1_CTX {
public:
    uint32_t state[5];
    uint32_t count[2];
    unsigned char buffer[64];
};

inline uint32_t rol(uint32_t value, size_t bits) {
    return (value << bits) | (value >> (32 - bits));
}

// Fix: blk now returns uint32_t
inline uint32_t blk(uint32_t block[16], int i) {
    block[i & 15] = rol(block[(i+13)&15] ^ block[(i+8)&15] ^ block[(i+2)&15] ^ block[i&15], 1);
    return block[i & 15];
}

#define R0(v,w,x,y,z,i) do { z += ((w&(x^y))^y) + block[i] + 0x5A827999 + rol(v,5); w=rol(w,30); } while(0)
#define R1(v,w,x,y,z,i) do { z += ((w&(x^y))^y) + blk(block,i) + 0x5A827999 + rol(v,5); w=rol(w,30); } while(0)
#define R2(v,w,x,y,z,i) do { z += (w^x^y) + blk(block,i) + 0x6ED9EBA1 + rol(v,5); w=rol(w,30); } while(0)
#define R3(v,w,x,y,z,i) do { z += (((w|x)&y)|(w&x)) + blk(block,i) + 0x8F1BBCDC + rol(v,5); w=rol(w,30); } while(0)
#define R4(v,w,x,y,z,i) do { z += (w^x^y) + blk(block,i) + 0xCA62C1D6 + rol(v,5); w=rol(w,30); } while(0)

std::string sha1(const std::string& input) {
    SHA1_CTX ctx;
    ctx.state[0]=0x67452301;
    ctx.state[1]=0xEFCDAB89;
    ctx.state[2]=0x98BADCFE;
    ctx.state[3]=0x10325476;
    ctx.state[4]=0xC3D2E1F0;
    ctx.count[0]=ctx.count[1]=0;

    uint64_t totalBits = input.size() * 8;
    std::vector<unsigned char> data(input.begin(), input.end());
    data.push_back(0x80);

    while ((data.size() % 64) != 56) data.push_back(0x00);

    for (int i = 7; i >= 0; --i) {
        data.push_back((totalBits >> (i*8)) & 0xFF);
    }

    for (size_t chunk=0; chunk<data.size(); chunk+=64) {
        uint32_t block[16];
        for(int i=0;i<16;i++) {
            block[i] = (data[chunk + i*4]<<24) | (data[chunk + i*4 + 1]<<16) |
                       (data[chunk + i*4 + 2]<<8) | (data[chunk + i*4 + 3]);
        }

        uint32_t a=ctx.state[0];
        uint32_t b=ctx.state[1];
        uint32_t c=ctx.state[2];
        uint32_t d=ctx.state[3];
        uint32_t e=ctx.state[4];

        R0(a,b,c,d,e,0); R0(e,a,b,c,d,1); R0(d,e,a,b,c,2); R0(c,d,e,a,b,3);
        R0(b,c,d,e,a,4); R0(a,b,c,d,e,5); R0(e,a,b,c,d,6); R0(d,e,a,b,c,7);
        R0(c,d,e,a,b,8); R0(b,c,d,e,a,9); R0(a,b,c,d,e,10); R0(e,a,b,c,d,11);
        R0(d,e,a,b,c,12); R0(c,d,e,a,b,13); R0(b,c,d,e,a,14); R0(a,b,c,d,e,15);
        for(int i=16;i<20;i++) R1(a,b,c,d,e,i);

        for(int i=20;i<40;i++) R2(a,b,c,d,e,i);
        for(int i=40;i<60;i++) R3(a,b,c,d,e,i);
        for(int i=60;i<80;i++) R4(a,b,c,d,e,i);

        ctx.state[0]+=a; ctx.state[1]+=b; ctx.state[2]+=c; ctx.state[3]+=d; ctx.state[4]+=e;
    }

    std::ostringstream result;
    for(int i=0;i<5;i++)
        result << std::hex << std::setw(8) << std::setfill('0') << ctx.state[i];
    return result.str();
}
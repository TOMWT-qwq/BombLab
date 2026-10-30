#include "defuser.h"

#include <inttypes.h>
#include <stdio.h>

#define MAX_FIELDS 8

/*
 * 把 values 中的 count 个整数写成一行“空格分隔的无符号十进制整数”，存入 out。
 * 成功返回 0；count 为 0（还没有实现）、snprintf 出错或结果被截断时返回非零。
 */
static int write_answer(char *out, size_t cap, const uint32_t *values, size_t count) {
    size_t used = 0;
    for (size_t i = 0; i < count; ++i) {
        int size = snprintf(out + used, cap - used, "%s%" PRIu32, i ? " " : "", values[i]);
        if (size < 0 || (size_t)size >= cap - used) return 1;
        used += (size_t)size;
    }
    return count == 0;
}

unsigned p1_step0(unsigned rdi,unsigned rsi)
{
    rdi-=rsi;
    return 5*rdi+0x31b;
}
unsigned p1_step1(unsigned rdi,unsigned rsi)
{
    return 5*rdi^(0x1a90+rsi);
}
unsigned p1_step2(unsigned rdi,unsigned rsi)
{
    return(rdi+rsi*2)^0x548e;
}
unsigned p1_compute(uint64_t rdi)
{
    unsigned r9d=rdi>>32;
    unsigned rdx=rdi>>16;
    unsigned r8d=rdi;
    unsigned rcx=p1_step0(rdi,r9d);
    return rcx^p1_step2(p1_step1(r9d,rdx),r8d);
}
int solve_phase_1(uint64_t challenge, char *out, size_t cap) {
    uint32_t values[MAX_FIELDS] = {0};
    size_t count = 1;
    values[0]=p1_compute(challenge);
    return write_answer(out, cap, values, count);
}

int solve_phase_2(uint64_t challenge, char *out, size_t cap) {
    uint32_t values[MAX_FIELDS] = {0};
    size_t count = 6;
    unsigned eax=values[0]=(challenge>>0x25&0xff)^0x19;
    unsigned ecx=0x16;
    uint64_t rdx=0x1;
    do{
        uint64_t rdi=challenge;
        eax+=rdx;
        rdi>>=ecx&0xff;
        eax*=3;
        rdi&=0x3f;
        eax-=rdi;
        values[rdx]=eax;
        ++rdx;
        ecx+=5;
    }while(rdx^6);
    return write_answer(out, cap, values, count);
}

int solve_phase_3(uint64_t challenge, char *out, size_t cap) {
    uint32_t values[MAX_FIELDS] = {0};
    size_t count = 2;
    unsigned edi=values[0]=challenge&7;
    unsigned eax=challenge>>3,esi=challenge>>32;
    esi^=eax;
    eax=edi;
    edi=esi;
    switch(eax)
    {
    case 0://p3_case_1
        values[1]=5*edi+0x44c9b;break;
    case 1://p3_case_5
        values[1]=5*edi+0xd881;break;
    case 2://p3_case_4
        values[1]=(edi^0x7543)+(edi>>1);break;
    case 3://p3_case_0
        values[1]=(2*edi)^0x70e5;break;
    case 4://p3_case_2
        values[1]=(edi^0x162b)+(edi>>1);break;
    case 5://p3_case_6
        values[1]=(4*edi)^0xe829;break;
    case 6://p3_case_3
        values[1]=3*edi+0xc962;break;
    case 7://p3_case_7
        values[1]=3*edi+0x18f9;break;
    }
    return write_answer(out, cap, values, count);
}

unsigned p4_walk(unsigned edi,unsigned esi,unsigned edx,uint64_t rcx)
{
    unsigned eax=edi;
    edi=edx;
    edi-=esi;
    edi>>=1;
    edi+=esi;
    if(edi==eax)
    {
        eax=edi+0x6b;
        return eax^=rcx;
    }
    if(eax>edi)return p4_walk(eax,1+edi,edx,rcx)*5^(edi+rcx)^0x1f;
    return p4_walk(eax,esi,-1+edi,rcx)*5^(edi+rcx)^0x13;
}
int solve_phase_4(uint64_t challenge, char *out, size_t cap) {
    uint32_t values[MAX_FIELDS] = {0};
    size_t count = 1;
    values[0]=p4_walk(challenge&0x7f,0,0x7f,(challenge>>7)^(challenge>>32));
    return write_answer(out, cap, values, count);
}

unsigned traverse(uint64_t rdi,unsigned*rsi)
{
    struct node{uint64_t a;unsigned b,c;};
    static struct node data[]={
        /* idx  addr      a   b       c      */
        /* 0  405ba0 */ {  6, 0x093e, 0x5e73 },
        /* 1  405bb0 */ { 10, 0x0463, 0x3b98 },
        /* 2  405bc0 */ {  8, 0x0324, 0x7183 },
        /* 3  405bd0 */ {  7, 0x0027, 0xb9d1 },
        /* 4  405be0 */ {  0, 0x0204, 0xc01b },
        /* 5  405bf0 */ {  0, 0x0b72, 0xe47d },
        /* 6  405c00 */ {  1, 0x011b, 0xaa3d },
        /* 7  405c10 */ { 11, 0x085c, 0x554b },
        /* 8  405c20 */ {  4, 0x0744, 0x6969 },
        /* 9  405c30 */ {  3, 0x0a5c, 0x9e64 },
        /* 10 405c40 */ {  2, 0x054b, 0xaae5 },
        /* 11 405c50 */ {  5, 0x0636, 0x8cf2 },
    };
    static unsigned head[8]={9,3,7,11,5,0,6,1};

    uint64_t rax=rdi;
    uint64_t rcx=rdi;
    rax&=7;
    rcx>>=3;
    unsigned rdx=head[rax];
    rax=rdi;
    rdi>>=32;
    rax>>=6;
    unsigned esi=data[rdx].b;
    rax^=rdi;
    rax^=data[rdx].c;rax&=0xffffffffu;
    rdi=rcx&0xffffffffu;
    rax^=0xc100u;
    *rsi=esi;
    rax=(rax+esi)&0xffffffffu;
    for(unsigned i=1;i<=(rdi&3);){
        rdx=data[rdx].a;
        ++i;
        esi=data[rdx].b;
        rax^=data[rdx].c;rax&=0xffffffffu;
        rax+=esi;rax&=0xffffffffu;
        *rsi=esi;
    }
    return rax;
}
int solve_phase_5(uint64_t challenge, char *out, size_t cap) {
    uint32_t values[MAX_FIELDS] = {0};
    size_t count = 2;
    unsigned tmp;
    unsigned eax=traverse(challenge,&tmp);
    values[0]=eax;values[1]=tmp;
    return write_answer(out, cap, values, count);
}

unsigned p6_op_0(unsigned x){return(((x<<5)+0x1a51)^x*5);}
unsigned p6_op_1(unsigned x){return((x^0x5797)+(x<<5));}
unsigned p6_op_2(unsigned x){return((x<<2)|(x>>30))^0xe1e1;}
unsigned p6_op_3(unsigned x){return((x>>3)|(x<<29));}
unsigned p6_op_4(unsigned x){return(((x>>1)^x)+0x70d8);}
unsigned p6_op_5(unsigned x){return((x+0xa941)^(x>>1));}
int solve_phase_6(uint64_t challenge, char *out, size_t cap) {
    uint32_t values[MAX_FIELDS] = {0};
    size_t count = 1;
    static unsigned(*p6_table[8])(unsigned)={
        p6_op_2,
        p6_op_5,
        p6_op_4,
        p6_op_0,
        p6_op_2,
        p6_op_1,
        p6_op_3,
        p6_op_0
    };
    unsigned edi=(challenge>>6)^(challenge>>32);
    unsigned ebx=challenge&0x38;
    unsigned eax=challenge&7;
    eax=p6_table[eax](edi);
    eax^=0xaedb;
    eax=p6_table[ebx>>3](eax);
    values[0]=eax+0x56e4u;
    return write_answer(out, cap, values, count);
}

unsigned secret_mix(unsigned edi)
{
    unsigned eax=edi;
    edi^=0xd3b3u;
    eax>>=5;
    eax^=0xf44du;
    return eax+=edi;
}
int solve_secret(uint64_t challenge, uint64_t context, char *out, size_t cap)
{
    uint64_t r13=context,r12=challenge;
    unsigned ecx=r13;
    ecx&=3;
    unsigned ans1=ecx;
    uint64_t rsi=r12;
    unsigned r9d=ecx*0xd3b3;
    uint64_t r8=r13;
    rsi>>=32;
    r8>>=32;
    rsi^=r12;rsi&=0xffffffffu;
    r8^=r13;r8&=0xffffffffu;
    r13>>=16;
    unsigned edi=rsi;
    r9d^=r13;
    edi^=r8;
    unsigned eax=secret_mix(edi);
    eax^=r9d;
    unsigned ans2=eax;
    rsi>>=5;rsi&=0xffffffffu;
    unsigned edx=0xf44d+r8+ecx;
    edx+=rsi;
    eax^=edx;
    unsigned ans3=eax;
    snprintf(out,cap,"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAOPEN %u %u %u",ans1,ans2,ans3);
    return 0;
}
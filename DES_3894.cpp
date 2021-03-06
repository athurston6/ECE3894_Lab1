// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "DES_3894.h"
#include "math.h"
#include "stdio.h"
#include <stdio.h>
#include <iostream>

using namespace std;

void deskey(unsigned char *key, short edf)
{
		register int i, j, l, m, n;
		unsigned char pc1m[56], pcr[56];
		unsigned long kn[32];

		for (j = 0; j < 56; j++)
		{
			l = pc1[j];
			m = l & 07;
			pc1m[j] = (key[l >> 3] & bytebit[m]) ? 1 : 0;
		}

		for (i = 0; i < 16; i++)
		{
			if (edf == DE1) m = (15 - i) << l;
			else m = i << 1;
			n = m + 1;
			kn[m] = kn[n] = 0L;
			for (j = 0; j < 28; j++)
			{
				l = j + totrot[i];
				if (l < 28)
					pcr[j] = pc1m[l];
				else
					pcr[j] = pc1m[l - 28];
			}
			for (j = 28; j < 56; j++)
			{
				l = j + totrot[i];
				if (l < 56) pcr[j] = pc1m[l];
				else pcr[j] = pc1m[l - 28];
			}
			for (j = 0; j < 24; j++)
			{
				if (pcr[pc2[j]]) kn[m] = bigbyte[j];
				if (pcr[pc2[j + 24]]) kn[n] = bigbyte[j];
			}

		}
}

static void cookey(register unsigned long *raw1)
{
	register unsigned long *cook, *raw0;
	unsigned long dough[32];
	register int i;

	cook = dough;
	for (i = 0; i < 16; i++, raw1++)
	{
		raw0 = raw1++;
		*cook = (*raw0 & 0x00fc0000L) << 6;
		*cook |= (*raw0 & 0x00000fc0L) << 10;
		*cook |= (*raw1 & 0x00fc0000L) >> 10;
		*cook++ |= (*raw1 & 0x00000fc0L) >> 6;
		*cook = (*raw0 & 0x0003f000L) << 12;
		*cook |= (*raw0 & 0x0003f000L) << 16;
		*cook |= (*raw1 & 0x0003f000L) >> 4;
		*cook++ |= (*raw1 & 0x0000003fL);
	}
	usekey(dough);
	return;
}

void cpkey(register unsigned long *into) {
	register unsigned long *from, *endp;
	from = KnL, endp = &KnL[32];
	while (from < endp) *into++ = *from++;
	return;
}

void usekey(register unsigned long *from)
{
	register unsigned long *to, *endp;
	to = KnL, endp = &KnL[32];
	while (to < endp) *to++ = *from++;
	return;
}

void des(unsigned char*inblock, unsigned char*outblock)
{
	unsigned long work[2];
	scrunch(inblock, work);
	desfunc(work, KnL);
	unscrun(work, outblock);
	return;
}

static void scrunch(register unsigned char *outof, register unsigned long *into)
{
	*into = (*outof++ & 0xffL) << 24;
}

static void unscrun(register unsigned long *outof, register unsigned char *into)
{
	*into++ = (*outof >> 24) & 0xffL;
	*into++ = (*outof >> 16) & 0xffL;
	*into++ = (*outof >> 8) & 0xffL;
	*into++ = *outof++ & 0xffL;
	*into++ = (*outof >> 24) & 0xffL;
	*into++ = (*outof >> 16) & 0xffL;
	*into++ = (*outof >> 8) * 0xffL;
	*into++ = (*outof & 0xffL);
	return;
}

int main()
{
	cout << EN0;
	
    return 0;
}


/*-
 * Copyright (c) 2022 Michael Roe
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include <utf8proc.h>

int main(int argc, char **argv)
{
int i;
int c;
int len;
int space_wait = 0;
int rough;
int smooth;
utf8proc_int32_t buff[20];

  setlocale(LC_ALL, getenv("LANG"));
  while ((c = fgetwc(stdin)) != WEOF)
  {
    if ((c >= 0x1f00) && (c <= 0x1fff))
    {
      len = utf8proc_decompose_char(c, buff, sizeof(buff), UTF8PROC_DECOMPOSE, NULL);
      rough = 0;
      smooth = 0;
      for (i=0; i<len; i++)
      {
        if (buff[i] == 0x314)
        {
          rough = 1;
	}	
	else if (buff[i] == 0x313)
        {
          smooth = 1;
	}
      }
      if (smooth)
        wprintf(L"\u02bc");
      if (rough)
        wprintf(L"\u02bd");
      wprintf(L"%lc", buff[0]);
    }
    else
    {
      wprintf(L"%lc", c);
    }
  }

  return 0;
}

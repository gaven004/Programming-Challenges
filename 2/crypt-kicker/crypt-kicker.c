/*
 * Crypt Kicker
 * PC/UVa IDs: 110204/843
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS_IN_DICTIONARY 1000
#define MAX_WORD_LENGTH 16
#define MAX_LINE_LENGTH 160

/* 字典，不同长度的词分组存储 */
char dict[MAX_WORD_LENGTH + 1][MAX_WORDS_IN_DICTIONARY][MAX_WORD_LENGTH + 1];
/* 字典中单词的个数，按长度分组 */
int nDWords[MAX_WORD_LENGTH + 1];

int is_unique(char words[][MAX_WORD_LENGTH + 1], int n) {
  int i;

  if (n) {
    for (i = 0; i < n; i++) {
      if (!strcmp(words[i], words[n])) {
        return 0;
      }
    }
  }

  return 1;
}

int split(const char *text, char words[][MAX_WORD_LENGTH + 1], int lEWords[],
          int *n) {
  int l;
  char *p;

  *n = l = 0, p = words[*n];
  while (*text) {
    if (*text == ' ' || *text == '\n') {
      *p = '\0';
      if (is_unique(words, *n)) {
        lEWords[*n] = l;
        (*n)++;
      }
      p = words[*n], l = 0;
    } else {
      *p = *text, p++, l++;
    }

    text++;
  }

  if (l) {
    *p = '\0';
    if (is_unique(words, *n)) {
      lEWords[*n] = l;
      (*n)++;
    }
  }

  return (*n);
}

int is_remap(const char map[]) {
  int i, k;
  char rmap[26];

  memset(rmap, 0, 26);

  for (i = 0; i < 26; i++) {
    if (map[i]) {
      k = map[i] - 'a';

      if (rmap[k]) {
        return 1;
      }

      rmap[k] = 'a' + i;
    }
  }

  return 0;
}

int try_map(const char *ciphertext, const char *dword, char map[], int l) {
  int i, k;

  for (i = 0; i < l; i++, ciphertext++, dword++) {
    k = *ciphertext - 'a';

    if (map[k]) {
      if (map[k] != (*dword)) {
        return 0;
      }
    } else {
      map[k] = *dword;
    }
  }

  if (is_remap(map)) {
    return 0;
  }

  return 1;
}

int decrypt(const char aEWords[][MAX_WORD_LENGTH + 1], const int lEWords[],
            char map[], int k, int n) {
  int i, l, r;
  char nmap[26];

  l = lEWords[k];

  for (i = 0; i < nDWords[l]; i++) {
    memcpy(nmap, map, 26);

    /* 尝试匹配 aEWords[k] 与 dict[l][i] */
    if (try_map(aEWords[k], dict[l][i], nmap, l)) {
      /* 最后一个单词，返回成功 */
      if (k + 1 == n) {
        memcpy(map, nmap, 26);
        return 1;
      }

      /* 否则解密下一个单词 */
      if (decrypt(aEWords, lEWords, nmap, k + 1, n)) {
        memcpy(map, nmap, 26);
        return 1;
      }
    }
  }

  return 0;
}

int main() {
  int nEWords; /* number of encrypted words */
  char aEWords[MAX_LINE_LENGTH][MAX_WORD_LENGTH + 1]; /* 密文单词 */
  int lEWords[MAX_LINE_LENGTH]; /* 密文单词的长度 */
  char mapping[26];

  int i, l, n, result;

  char buff[MAX_LINE_LENGTH + 1];

  /* 初始化字典 */
  for (i = 0; i <= MAX_WORD_LENGTH; i++) {
    nDWords[i] = 0;
  }

  scanf("%d", &n);
  for (i = 0; i < n; i++) {
    scanf("%s", buff);
    l = strlen(buff);
    strcpy(dict[l][nDWords[l]], buff);
    nDWords[l]++;
  }

  fgets(buff, MAX_LINE_LENGTH + 1, stdin); /* the last \n */

  /* 读入密文 */
  while (fgets(buff, MAX_LINE_LENGTH + 1, stdin) != NULL) {

    split(buff, aEWords, lEWords, &nEWords);

    /* 解密 */
    memset(mapping, 0, 26);
    result = decrypt(aEWords, lEWords, mapping, 0, nEWords);

    /* 输出 */
    for (i = 0; buff[i]; i++) {
      if (buff[i] == '\n') {
        break;
      } else if (buff[i] == ' ') {
        putchar(' ');
      } else {
        putchar(result ? mapping[buff[i] - 'a'] : '*');
      }
    }
    putchar('\n');
  }

  return 0;
}

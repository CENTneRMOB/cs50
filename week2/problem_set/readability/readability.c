#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

int count_letters(string text);
int count_sentences(string text);
int count_words(string text);

int main(void) 
{
  string text = get_string("Text: ");
  int letters_count = count_letters(text);
  int words_count = count_words(text);
  int sentences_count = count_sentences(text);

  float letters_avg = ((float) letters_count / (float) words_count) * 100;
  float sentence_avg = ((float) sentences_count / (float) words_count) * 100;

  float float_index = (0.0588 * letters_avg) - (0.296 * sentence_avg) - 15.8;
  int index = round(float_index);

  if (index >= 16)
  {
    printf("Grade 16+\n");
  }
  else if (index < 1)
  {
    printf("Before Grade 1\n");
  }
  else
  {
    printf("Grade %i\n", index);
  }
}

int count_letters(string text)
{
  int count = 0;

  for (int i = 0; i < strlen(text); i++)
  {
    if (text[i] >= 'A' && text[i] <= 'Z')
    {
      count += 1;
    }
    else if (text[i] >= 'a' && text[i] <= 'z')
    {
      count += 1;
    }
  }

  return count;
}

int count_sentences(string text)
{
  int count = 0;

  for (int i = 0; i < strlen(text); i++)
  {
    if (text[i] == 46 || text[i] == 33 || text[i] == 63)
    {
      count += 1;
    }
  }

  return count;
}

int count_words(string text)
{
  int count = 0;

  for (int i = 0; i < strlen(text); i++)
  {
    if (text[i] == 32)
    {
      count += 1;
    }
  }

  return count + 1;
}
#include <stdio.h>
#include <stdlib.h>
#include <hunspell/hunspell.h>

char* Spellcheck(char *word)
{
	Hunhandle *h = Hunspell_create(
		"/usr/share/hunspell/en_US.aff",
		"/usr/share/hunspell/en_US.dic"
	);

	int correct = Hunspell_spell(h, word);
	if(correct == 0)
	{
		char ***s = malloc(sizeof(char));
		Hunspell_suggest(h, s, word);
		Hunspell_destroy(h);
		if (*s != NULL)
		{
			return s[0][0];
		}
	}
	return word;
}
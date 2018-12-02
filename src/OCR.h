#ifndef OCR_H
#define OCR_H

void OCR_Debug(char *path);
char *OCR_Start(
	char *path,
	int enableDebugMode,
	int enableFilters,
	int enablePostprocessing
);
void OCR_ExportAsTextFile(char *path);

#endif

P3FS: P3FS.c P3console.c impl.c LibDisk.c
	gcc P3FS.c P3console.c impl.c LibDisk.c -std=c99 -o P3FS -Werror -Wall
run: P3FS
	./P3FS
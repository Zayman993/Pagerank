CC=gcc
FLAGS=-Wall

pageRank: pageRank.c functions.c pageRank.h
	$(CC) -o pageRank_exe pageRank.c functions.c $(FLAGS)

clean:
	rmdir -f ../HPC
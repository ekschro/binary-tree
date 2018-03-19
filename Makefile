all:
	gcc evenSumRange.c -o evenSumRange
	gcc balancedEvenSumRange.c -o balancedEvenSumRange
	
unbalanced:
	gcc evenSumRange.c -o evenSumRange

balanced:
	gcc balancedEvenSumRange.c -o balancedEvenSumRange

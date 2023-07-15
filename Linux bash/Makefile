

textfiles.txt:
	for i in 1 2 3 4 5 6 7 8 9 10; do echo "Testing $$i" > $$i.txt; done

%.TXT: %.txt
	tr 'a-z' 'A-Z' < $< > $@

clean:
	rm *.txt
	rm *.TXT

mean: 
	sum=0;
	for n in *; do echo $$(basename $$n); done

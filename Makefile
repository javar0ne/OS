folder_path = $(shell pwd)/$(path)

run: create_folder copy_files

create_folder:
	mkdir $(folder_path)
	mkdir $(folder_path)/tpl

copy_files:
	cp -r $(shell pwd)/tpl/C/C_template $(folder_path)/tpl/C_template
	cp $(shell pwd)/tpl/C/Makefile $(folder_path)/Makefile 

release:
	git add SO
	git commit -m "feat: SO"
	git push

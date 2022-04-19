

ALLEGRO_LIBS=allegro_color allegro_font allegro_ttf allegro_dialog allegro_audio allegro_acodec allegro_primitives allegro_image allegro
ALLEGRO_LIBS_MAIN=$(ALLEGRO_LIBS) allegro_main
ALLEGRO_LIBS_LINK_ARGS := $(ALLEGRO_LIBS:%=-l%)
ALLEGRO_LIBS_LINK_MAIN_ARGS := $(ALLEGRO_LIBS_MAIN:%=-l%)


all: programs
	@echo "== Build Finished =="


objs: main.cpp
	g++ -c -o obj/main.o main.cpp


programs: objs
	g++ -o bin/bearys_bash obj/main.o $(ALLEGRO_LIBS_LINK_MAIN_ARGS)


clean:
	-rm obj/main.o
	-rm bin/bearys_bash



INC	= -Iinclude/ -I../bullet/include/bullet -I../skylib/include/ -IC:/boost/boost_1_52_0/
SKYLIB = -L../skylib/lib -lsky
BULLET = -L../bullet/lib/ -lBulletDynamics -lBulletCollision -lLinearMath
LIBS = ${SKYLIB} ${BULLET} -lopengl32 -lSDL -ljson

skylib_test: obj/main.o obj/menu_state.o obj/test_state.o obj/object.o obj/level.o obj/font.o
	g++ -Wall $^ -o bin/$@ ${LIBS} -Wl,-subsystem,windows -mwindows

obj/main.o: src/main.cc obj/menu_state.o obj/test_state.o obj/level.o
	g++ -Wall ${INC} -c src/main.cc -o $@

obj/test_state.o: src/test_state.cc include/skylib_test/test_state.h obj/object.o obj/level.o obj/font.o
	g++ ${INC} -c src/test_state.cc -o $@

obj/menu_state.o: src/menu_state.cc include/skylib_test/menu_state.h obj/object.o obj/level.o obj/font.o
	g++ ${INC} -c src/menu_state.cc -o $@

obj/object.o: src/object.cc include/skylib_test/object.h
	g++ ${INC} -c src/object.cc -o $@

obj/level.o: src/level.cc include/skylib_test/level.h
	g++ ${INC} -c src/level.cc -o $@

obj/font.o: src/font.cc include/skylib_test/font.h
	g++ ${INC} -c src/font.cc -o $@

clean:
	rm -rf obj/*.o
	rm -rf bin/*.exe

INC	= -Iinclude/ -IC:/boost/boost_1_52_0/ -I../bullet/include/bullet

libsky: obj/engine.o obj/state.o obj/state_manager.o obj/color.o obj/resource.o obj/resource_manager.o obj/model.o obj/texture.o obj/sprite.o obj/vector.o obj/matrix.o obj/vertex.o obj/vertex_color.o obj/vertex_normal.o obj/vertex_normal_color.o obj/vertex_normal_texture.o obj/vertex_texture.o obj/triangulate.o obj/stb_image.o
	ar crf lib/$@.a $^

obj/engine.o: src/engine.cc include/skylib/engine.h include/skylib/state_manager.h include/skylib/common/color.h
	g++ ${INC} -c src/engine.cc -o $@

obj/state.o: src/state.cc include/skylib/state.h
	g++ ${INC} -c src/state.cc -o $@

obj/state_manager.o: src/state_manager.cc include/skylib/state_manager.h include/skylib/state.h
	g++ ${INC} -c src/state_manager.cc -o $@

obj/vector.o: src/math/vector.cc include/skylib/math/vector.h
	g++ ${INC} -c src/math/vector.cc -o $@

obj/matrix.o: src/math/matrix.cc include/skylib/math/matrix.h include/skylib/math/vector.h include/skylib/math/definitions.h
	g++ ${INC} -c src/math/matrix.cc -o $@

obj/color.o: src/common/color.cc include/skylib/common/color.h include/skylib/math/vector.h
	g++ ${INC} -c src/common/color.cc -o $@

obj/resource.o: src/resource/resource.cc include/skylib/resource/resource.h
	g++ ${INC} -c src/resource/resource.cc -o $@

obj/resource_manager.o: src/resource/resource_manager.cc include/skylib/resource/resource_manager.h
	g++ ${INC} -c src/resource/resource_manager.cc -o $@

obj/model.o: src/resource/model.cc include/skylib/resource/model.h include/skylib/vertex/batch.h include/skylib/resource/resource.h
	g++ ${INC} -c src/resource/model.cc -o $@

obj/texture.o: src/resource/texture.cc include/skylib/resource/texture.h include/skylib/resource/resource.h
	g++ ${INC} -c src/resource/texture.cc -o $@

obj/sprite.o: src/resource/sprite.cc include/skylib/resource/sprite.h include/skylib/resource/texture.h
	g++ ${INC} -c src/resource/sprite.cc -o $@

obj/vertex.o: src/vertex/vertex.cc include/skylib/vertex/vertex.h
	g++ ${INC} -c src/vertex/vertex.cc -o $@

obj/vertex_color.o: src/vertex/vertex_color.cc include/skylib/vertex/vertex_color.h
	g++ ${INC} -c src/vertex/vertex_color.cc -o $@

obj/vertex_normal.o: src/vertex/vertex_normal.cc include/skylib/vertex/vertex_normal.h
	g++ ${INC} -c src/vertex/vertex_normal.cc -o $@

obj/vertex_normal_color.o: src/vertex/vertex_normal_color.cc include/skylib/vertex/vertex_normal_color.h
	g++ ${INC} -c src/vertex/vertex_normal_color.cc -o $@

obj/vertex_normal_texture.o: src/vertex/vertex_normal_texture.cc include/skylib/vertex/vertex_normal_texture.h
	g++ ${INC} -c src/vertex/vertex_normal_texture.cc -o $@

obj/vertex_texture.o: src/vertex/vertex_texture.cc include/skylib/vertex/vertex_texture.h
	g++ ${INC} -c src/vertex/vertex_texture.cc -o $@

obj/triangulate.o: src/math/triangulate.cc include/skylib/math/triangulate.h include/skylib/math/vector.h
	g++ ${INC} -c src/math/triangulate.cc -o $@

obj/stb_image.o: src/resource/stb_image.c include/skylib/resource/stb_image.h
	gcc ${INC} -c src/resource/stb_image.c -o $@

clean:
	rm -rf obj/*.o
	rm -rf lib/*.a

CXXFLAGS = -std=c++17 -Wall -Wextra -Wno-sign-compare
LDFLAGS = -Llib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf #-lSDL2_mixer
INCFLAGS = -Iinclude -Iinclude/TinyXML -Iinclude/SDL2 -IECS/include -IEngine/include -IComponents/include -ISystems/include -ICollisions/include -IMap/include

all: clean bin/Game launch

+#execution du jeu (facultatif)
launch:
	bin/Game.exe

#executable
bin/Game: obj/main.o obj/Engine.o obj/AssetsLoader.o obj/Manager.o obj/tinystr.o obj/tinyxml.o obj/tinyxmlerror.o obj/tinyxmlparser.o obj/icon.res
	g++ $(CXXFLAGS) -o bin/Game obj/main.o obj/Engine.o obj/AssetsLoader.o obj/Manager.o obj/tinystr.o obj/tinyxml.o obj/tinyxmlerror.o obj/tinyxmlparser.o obj/icon.res $(INCFLAGS) $(LDFLAGS) 

#objets du jeu
obj/main.o: main.cpp 
	g++ $(CXXFLAGS) -o obj/main.o -c main.cpp $(INCFLAGS) $(LDFLAGS)

obj/Engine.o: Engine/src/Engine.cpp
	g++ $(CXXFLAGS) -o obj/Engine.o -c Engine/src/Engine.cpp $(INCFLAGS) $(LDFLAGS)

obj/AssetsLoader.o: Engine/src/AssetsLoader.cpp
	g++ $(CXXFLAGS) -o obj/AssetsLoader.o -c Engine/src/AssetsLoader.cpp $(INCFLAGS) $(LDFLAGS)

obj/Manager.o: ECS/src/Manager.cpp
	g++ $(CXXFLAGS) -o obj/Manager.o -c ECS/src/Manager.cpp $(INCFLAGS) $(LDFLAGS)

#objets de TinyXML
obj/tinystr.o: include/TinyXML/tinystr.cpp
	g++ $(CXXFLAGS) -o obj/tinystr.o -c include/TinyXML/tinystr.cpp $(INCFLAGS) $(LDFLAGS)

obj/tinyxml.o: include/TinyXML/tinyxml.cpp
	g++ $(CXXFLAGS) -o obj/tinyxml.o -c include/TinyXML/tinyxml.cpp $(INCFLAGS) $(LDFLAGS)

obj/tinyxmlerror.o: include/TinyXML/tinyxmlerror.cpp
	g++ $(CXXFLAGS) -o obj/tinyxmlerror.o -c include/TinyXML/tinyxmlerror.cpp $(INCFLAGS) $(LDFLAGS)

obj/tinyxmlparser.o: include/TinyXML/tinyxmlparser.cpp
	g++ $(CXXFLAGS) -o obj/tinyxmlparser.o -c include/TinyXML/tinyxmlparser.cpp $(INCFLAGS) $(LDFLAGS)

#icone de l'executable
obj/icon.res:
	windres res/icon.rc -O coff -o obj/icon.res

#nettoyage
clean:
	del obj\*.o bin\*.exe
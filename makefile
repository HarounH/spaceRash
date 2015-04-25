UNAME := $(shell uname)
Compiler=g++ -std=c++11
SRC=Source/
OBJ=Objects/
EXE=Executable/
RSC=Resource/ 
EXEC=spaceRash.out
Files=*.o
#FOR LINUX
ifeq ($(UNAME), Linux)
LIBS= -lpthread -lBulletSoftBody -lBulletDynamics -lBulletCollision -lLinearMath -lboost_system -lboost_thread -lboost_serialization -lsfgui -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lGL -lGLU
INCS=-I/usr/include/bullet
HELP= $(SRC)helpers.hpp
$(EXEC):  $(OBJ)message.o $(OBJ)userSettings.o  $(OBJ)skybox.o  $(OBJ)networkManager.o $(OBJ)weapon.o  $(OBJ)spaceObject_load.o $(OBJ)spaceObject_render.o $(OBJ)HUD.o $(OBJ)spaceObject_event.o $(OBJ)spaceObject_getsets.o $(OBJ)ObjManager.o $(OBJ)Obj_Loader.o  $(OBJ)startJoinScreen.o $(OBJ)selectShipScreen.o $(OBJ)AI.o $(OBJ)player.o $(OBJ)player_world.o $(OBJ)player_event.o $(OBJ)player_getsets.o $(OBJ)player_network.o $(OBJ)player_handle.o $(OBJ)main.o
	$(Compiler) $^ $(LIBS) -o $@ 

all:
	make $(EXEC)

$(OBJ)selectShipScreen.o: $(SRC)selectShipScreen.hpp $(SRC)selectShipScreen.cpp
	$(Compiler) -c $(SRC)selectShipScreen.cpp $(INCS)
	mv selectShipScreen.o $@

$(OBJ)startJoinScreen.o: $(SRC)startJoinScreen.hpp $(SRC)startJoinScreen.cpp
	$(Compiler) -c $(SRC)startJoinScreen.cpp $(INCS)
	mv startJoinScreen.o $@

$(OBJ)spaceObject_load.o: $(SRC)spaceObject_load.cpp
	$(Compiler) -c $^ $(INCS)
	mv spaceObject_load.o $@

$(OBJ)spaceObject_render.o: $(SRC)spaceObject_render.cpp 
	$(Compiler) -c $^ $(INCS)
	mv spaceObject_render.o $@

$(OBJ)spaceObject_event.o: $(SRC)spaceObject_event.cpp 
	$(Compiler) -c $^ $(INCS)
	mv spaceObject_event.o $@

$(OBJ)spaceObject_getsets.o: $(SRC)spaceObject_getsets.cpp 
	$(Compiler) -c $^ $(INCS)
	mv spaceObject_getsets.o $@

$(OBJ)player.o: $(SRC)player.cpp
	$(Compiler) -c $^ $(INCS)
	mv player.o $@

$(OBJ)player_event.o: $(SRC)player_event.cpp
	$(Compiler) -c $^ $(INCS)
	mv player_event.o $@

$(OBJ)player_world.o: $(SRC)player_world.cpp
	$(Compiler) -c $^ $(INCS)
	mv player_world.o $@

$(OBJ)player_getsets.o: $(SRC)player_getsets.cpp
	$(Compiler) -c $^ $(INCS)
	mv player_getsets.o $@

$(OBJ)player_network.o: $(SRC)player_network.cpp
	$(Compiler) -c $^ $(INCS)
	mv player_network.o $@

$(OBJ)player_handle.o: $(SRC)player_handle.cpp
	$(Compiler) -c $^ $(INCS)
	mv player_handle.o $@

$(OBJ)main.o: $(SRC)main.cpp
	$(Compiler) -c $< $(INCS)
	mv main.o $@

$(OBJ)skybox.o: $(SRC)skybox.cpp
	$(Compiler) -c $< $(INCS)
	mv skybox.o $@

$(OBJ)networkManager.o: $(SRC)networkManager.cpp
	$(Compiler) -c $< $(INCS)
	mv networkManager.o $@

$(OBJ)userSettings.o: $(SRC)userSettings.cpp
	$(Compiler) -c $^ $(INCS)
	mv userSettings.o $@

$(OBJ)weapon.o: $(SRC)weapon.cpp
	$(Compiler) -c $^ $(INCS)
	mv weapon.o $@

$(OBJ)message.o: $(SRC)message.cpp
	$(Compiler) -c $^ $(INCS)
	mv message.o $@

$(OBJ)ObjManager.o: $(SRC)ObjManager.cpp
	$(Compiler) -c $^ $(INCS)
	mv ObjManager.o $@

$(OBJ)AI.o: $(SRC)AI.cpp
	$(Compiler) -c $^ $(INCS)
	mv AI.o $@

$(OBJ)Obj_Loader.o: $(SRC)obj_Loader.cpp
	$(Compiler) -c $^ $(INCS)
	mv obj_Loader.o $@

$(OBJ)HUD.o: $(SRC)HUD.cpp
	$(Compiler) -c $^ $(INCS)
	mv HUD.o $@

execute: $(EXEC)
	./$<

clean:
	rm $(EXEC) $(OBJ)*
cleanFiles:
	rm $(Files) 
endif

#FOR MAC
ifeq ($(UNAME), Darwin)
LIBS=-lBulletSoftBody -lBulletDynamics -lBulletCollision -lLinearMath -lboost_system -lboost_thread-mt -lboost_serialization -lsfgui -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
INCS=-I /usr/local/Cellar/bullet/2.82/include/bullet/
FRAMEWORKS=-framework OpenGL -framework GLUT

$(EXEC):  $(OBJ)message.o $(OBJ)userSettings.o  $(OBJ)skybox.o  $(OBJ)networkManager.o $(OBJ)weapon.o  $(OBJ)spaceObject_load.o $(OBJ)spaceObject_render.o $(OBJ)spaceObject_event.o $(OBJ)spaceObject_getsets.o $(OBJ)selectShipScreen.o $(OBJ)startJoinScreen.o $(OBJ)HUD.o $(OBJ)AI.o $(OBJ)player.o $(OBJ)player_world.o $(OBJ)player_event.o $(OBJ)player_getsets.o $(OBJ)player_network.o $(OBJ)player_handle.o $(OBJ)main.o $(OBJ)ObjManager.o $(OBJ)Obj_Loader.o
	$(Compiler) $^ $(LIBS) $(FRAMEWORKS) -o $@ 

all:
	make $(EXEC)

$(OBJ)selectShipScreen.o: $(SRC)selectShipScreen.hpp $(SRC)selectShipScreen.cpp
	$(Compiler) -c $(SRC)selectShipScreen.cpp $(INCS)
	mv selectShipScreen.o $@

$(OBJ)startJoinScreen.o: $(SRC)startJoinScreen.hpp $(SRC)startJoinScreen.cpp
	$(Compiler) -c $(SRC)startJoinScreen.cpp $(INCS)
	mv startJoinScreen.o $@

$(OBJ)spaceObject_load.o: $(SRC)spaceObject_load.cpp
	$(Compiler) -c $^ $(INCS)
	mv spaceObject_load.o $@

$(OBJ)spaceObject_render.o: $(SRC)spaceObject_render.cpp 
	$(Compiler) -c $^ $(INCS)
	mv spaceObject_render.o $@

$(OBJ)spaceObject_event.o: $(SRC)spaceObject_event.cpp 
	$(Compiler) -c $^ $(INCS)
	mv spaceObject_event.o $@

$(OBJ)spaceObject_getsets.o: $(SRC)spaceObject_getsets.cpp 
	$(Compiler) -c $^ $(INCS)
	mv spaceObject_getsets.o $@

$(OBJ)player.o: $(SRC)player.cpp
	$(Compiler) -c $^ $(INCS)
	mv player.o $@

$(OBJ)player_event.o: $(SRC)player_event.cpp
	$(Compiler) -c $^ $(INCS)
	mv player_event.o $@

$(OBJ)player_world.o: $(SRC)player_world.cpp
	$(Compiler) -c $^ $(INCS)
	mv player_world.o $@

$(OBJ)player_getsets.o: $(SRC)player_getsets.cpp
	$(Compiler) -c $^ $(INCS)
	mv player_getsets.o $@

$(OBJ)player_network.o: $(SRC)player_network.cpp
	$(Compiler) -c $^ $(INCS)
	mv player_network.o $@

$(OBJ)player_handle.o: $(SRC)player_handle.cpp
	$(Compiler) -c $^ $(INCS)
	mv player_handle.o $@

$(OBJ)main.o: $(SRC)main.cpp
	$(Compiler) -c $< $(INCS)
	mv main.o $@

$(OBJ)skybox.o: $(SRC)skybox.cpp
	$(Compiler) -c $< $(INCS)
	mv skybox.o $@

$(OBJ)networkManager.o: $(SRC)networkManager.cpp
	$(Compiler) -c $< $(INCS)
	mv networkManager.o $@

$(OBJ)userSettings.o: $(SRC)userSettings.cpp
	$(Compiler) -c $^ $(INCS)
	mv userSettings.o $@

$(OBJ)weapon.o: $(SRC)weapon.cpp
	$(Compiler) -c $^ $(INCS)
	mv weapon.o $@

$(OBJ)message.o: $(SRC)message.cpp
	$(Compiler) -c $^ $(INCS)
	mv message.o $@

$(OBJ)ObjManager.o: $(SRC)ObjManager.cpp
	$(Compiler) -c $^ $(INCS)
	mv ObjManager.o $@

$(OBJ)AI.o: $(SRC)AI.cpp
	$(Compiler) -c $^ $(INCS)
	mv AI.o $@

$(OBJ)Obj_Loader.o: $(SRC)obj_Loader.cpp
	$(Compiler) -c $^ $(INCS)
	mv obj_Loader.o $@

$(OBJ)HUD.o: $(SRC)HUD.cpp
	$(Compiler) -c $^ $(INCS)
	mv HUD.o $@

execute: $(EXEC)
	./$<

clean:
	rm $(EXEC) $(OBJ)*
cleanFiles:
	rm $(Files) 
endif
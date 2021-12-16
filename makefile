all: airportDash

airportDash: main.o airport.o flightInstance.o flightLeg.o flightlegInstance.o flightTable.o pasenger.o pilot.o plane.o planeSeats.o planetypeTable.o reservation.o
	g++ -o airportDash main.o airport.o flightInstance.o flightLeg.o flightlegInstance.o flightTable.o pasenger.o pilot.o plane.o planeSeats.o planetypeTable.o reservation.o

airport.o: airport.cpp airport.h
	g++ -c airport.cpp

main.o: main.cpp
	g++ -c main.cpp

flightInstance.o: flightInstance.cpp flightInstance.h
	g++ -c flightInstance.cpp

flightLeg.o: flightLeg.cpp flightLeg.h
	g++ -c flightLeg.cpp

flightlegInstance.o: flightlegInstance.cpp flightlegInstance.h
	g++ -c flightlegInstance.cpp

flightTable.o: flightTable.cpp flightTable.h
	g++ -c flightTable.cpp

pasenger.o: pasenger.cpp passenger.h
	g++ -c pasenger.cpp

pilot.o: pilot.cpp pilot.h
	g++ -c pilot.cpp

plane.o: plane.cpp plane.h
	g++ -c plane.cpp

planeSeats.o: planeSeats.cpp planeSeats.h
	g++ -c planeSeats.cpp

planetypeTable.o: planetypeTable.cpp planetypeTable.h
	g++ -c planetypeTable.cpp

reservation.o: reservation.cpp reservation.h
	g++ -c reservation.cpp

clean: 
	rm *.o airportDash

# Welcome to RoboCIn Simulation 2D

This repository will guide you to install Simulation 2D environment 

[![RSS 2D](http://img.youtube.com/vi/Ptzv9NF9opM/0.jpg)](https://www.youtube.com/watch?v=Ptzv9NF9opM "Robot Soccer Simulator 2D")

## Install Dependencies

 0. You need to install project [libs](https://github.com/robocin/simulation-2d/tree/master/libs). Go to folder and copy
 libs to your local libs path, and link it.
 	
 		cd libs/
		sudo cp librcss* /usr/local/lib/

	Now you need to link it:

		(Open with a text editor in sudo mode)
		sudo subl /etc/ld.so.conf.d/local.conf # here we used sublime, but you can use gedit or vi

	Write these path in the file and save it:
	
		/usr/local/share

	Update your ldconfig:

		sudo ldconfig

	If after each part installation, you have a lib error, try to run the command above again.


 1. **Install** [Flex](https://github.com/westes/flex) **and** [Bison](https://www.gnu.org/software/bison/ ):
		
		sudo apt-get update
		sudo apt-get upgrade
		sudo apt-get install flex bison
		
	After install, check if everything is ok:

	    which flex
	    which bison

 2. **Install libs to help in building process**:
 
	    sudo apt-get install libaudio-dev libpng-dev libxi-dev libglib2.0-dev libfontconfig-dev libxrender-dev libtool libboost-all-dev autoconf libqt4-dev libxt-dev

 3. **Install each part of environment**:
 
	3.1 Install [rcssserver](https://github.com/rcsoccersim/rcssserver):
		
		cd rcssserver
		sudo ./bootstrap
	    sudo ./configure
	    sudo make
	    sudo make install
	    cd ..

	3.2 Install [rcsslogplayer](https://github.com/rcsoccersim/rcsslogplayer)

		cd rcsslogplayer
		sudo ./bootstrap
	    sudo ./configure
	    sudo make
	    sudo make install
	    cd ..
	
	3.3 Install [rcssmonitor](https://github.com/rcsoccersim/rcssmonitor)
	
		cd rcssmonitor
		sudo ./bootstrap
	    sudo ./configure
	    sudo make
	    sudo make install


	If there is any error, try to read [Compilation Error](https://github.com/robocin/simulation-2d#compilation-error), or if doesn´t have, you can open an issue.

	Tree process:
	
	![alt text](https://github.com/robocin/simulation-2d/blob/master/images/flowchartProcess.png)


 4. **After installation you can run each project part in different terminal**:
 
		ctrl + alt + T
	    rcssserver	# if it doesn´t work, try to run as sudo
    
	![alt text](https://github.com/robocin/simulation-2d/blob/master/images/rcssserver.png)


	    ctrl + shift + T
	    rcssmonitor # if it doesn´t work, try to run as sudo

	![alt text](https://github.com/robocin/simulation-2d/blob/master/images/rcssmonitor.png)

	    
	    ctrl + shift + T
	    rcsslogplayer # if it doesn´t work, try to run as sudo
	
	![alt text](https://github.com/robocin/simulation-2d/blob/master/images/rcsslogplayer.png)


	    ctrl + shift + T
	    Run your team code (In Item 6: there are two teams projects to download)

	![alt text](https://github.com/robocin/simulation-2d/blob/master/images/rcssteam.png)


 5. **You can download some open source team and try to modify it**:

	[Python Team](https://github.com/kengz/robocup-soccer)

	[C++ Team](https://github.com/wrighteagle2d/wrighteaglebase)

I couldn`t put the python team to work, but the c++  worked very well, you can download, install and run it:

	git clone https://github.com/wrighteagle2d/wrighteaglebase
	cd wrighteaglebase
	sudo make
	./start.sh # These command will start a team in left side
	ctrl + shift + T
	./start.sh -t [TEAMNAME] # These command will start a team in right side
	ctrl + K # These command will start the game, have fun! :)


## Compilation Error

If you are facing these error:

![alt text](https://github.com/robocin/simulation-2d/blob/master/images/errorImages/autoConfError.png)

Or these:

![alt text](https://github.com/robocin/simulation-2d/blob/master/images/errorImages/runAsSudo.png?raw=true)

Try to run the command as **sudo**, or install [autoconfig](https://askubuntu.com/questions/430706/installing-autotools-autoconf/638558) and dh-autoconfig

![alt text](https://github.com/robocin/simulation-2d/blob/master/images/errorImages/autoConfSudo.png)

If you have problems with libs, like **librcssclangparser**:

![alt text](https://github.com/robocin/simulation-2d/blob/master/images/errorImages/librcssparser.png)

Or these:

![alt text](https://github.com/robocin/simulation-2d/blob/master/images/errorImages/needToLink.png)

You need to create these file (like says in [item 0](https://github.com/robocin/simulation-2d#install-dependencies) and save it:

![alt text](https://github.com/robocin/simulation-2d/blob/master/images/errorImages/usrLocalShare.png)

Update your ldconfig, and run the command of your installation part (sudo rcssserver ...):

![alt text](https://github.com/robocin/simulation-2d/blob/master/images/errorImages/sudoLdConfig.png)


If you are having the same link error again, like image below, you only need to **sudo ldconfig**, to update ldconf:

![alt text](https://github.com/robocin/simulation-2d/blob/master/images/errorImages/trySudoLdConfigAgain.png)

	sudo ldconfig

If you have problems to execute **sudo make** in paste **/rcssmonitor** and the error is:
![alt text](https://github.com/robocin/simulation-2d/blob/master/images/errorImages/sudoMakeMonitor.png)

You execute this line:

	sudo apt-get install libxt-dev

If you have other compilation error, open an issue and we will try to help you fixing it.


## Run with Docker 

 0. You need to install [Docker](https://docs.docker.com/install/) and clone this [project](https://github.com/robocin/simulation-2d).
 1. Go to simulation-2d folder and build docker image (It will take something like 20 minutes or more, depends of your network speed. Because It´s pulls Ubuntu image and install all dependencies. Don´t change the tree files of this project!). This command only need to run once.
			
		docker build . -t "simulator2d:core"
 
 2.  Now, you need to [create a docker network](https://docs.docker.com/engine/reference/commandline/network_create/), to bypass data between containers in bridge mode. The IP receive the alias of container´s name.
 
		 docker network create mynet

3. You need to make the Display exportable

		 xhost +local:root

4. Run and have fun! Each command below, need to be run in a different terminal (ctrl+alt+t and ctrl+shift+t)
	
	Run the server (Run **twice the command rcssserver**, to create log folder and to work correctly):
		
		docker run -it --rm -e DISPLAY=${DISPLAY} -e QT_X11_NO_MITSHM=1 -v /tmp/.X11-unix:/tmp/.X11-unix --name=server --net mynet simulator2d:core
		
		rcssserver 
		rcssserver

	Run the logger

		docker run -it --rm -e DISPLAY=${DISPLAY} -e QT_X11_NO_MITSHM=1 -v /tmp/.X11-unix:/tmp/.X11-unix --name=logplayer --net mynet simulator2d:core
		rcsslogplayer
		
	Click in **Monitor** inside rcsslogplayer window, choose **connect to** and **type**: server, then click in **Ok**.

	Run the monitor
	
		docker run -it --rm -e DISPLAY=${DISPLAY} -e QT_X11_NO_MITSHM=1 -v /tmp/.X11-unix:/tmp/.X11-unix --name=monitor --net mynet simulator2d:core 

	Click in **Monitor** inside rcssmonitor window, choose **connect to** and **type**: server, then click in **Ok**.
		
	Run your first team:

		docker run -it --rm -e DISPLAY=${DISPLAY} -e QT_X11_NO_MITSHM=1 -v /tmp/.X11-unix:/tmp/.X11-unix --name=team1 --net mynet simulator2d:core 
		Download your team with clone or wget (need to change ip to connect to server)

	Run your second team: 
		
		docker run -it --rm -e DISPLAY=${DISPLAY} -e QT_X11_NO_MITSHM=1 -v /tmp/.X11-unix:/tmp/.X11-unix --name=team2 --net mynet simulator2d:core 
		Download your team with clone or wget (need to change ip to connect to server)



## Tutorial Authors

* **Heitor Rapela** -- [heitorrapela](https://github.com/heitorrapela)
* **Juliana Damurie** -- [JulianaDamurie](https://github.com/JulianaDamurie)

## Acknowledgments

These tutorial were created based on https://github.com/rcsoccersim

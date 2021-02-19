# Copyright (c) 2010 
# 
# This file is part of LTE-Sim
# LTE-Sim is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License version 3 as
# published by the Free Software Foundation;
# 
# LTE-Sim is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with LTE-Sim; if not, see <http://www.gnu.org/licenses/>.
#
# Author: Mauricio Iturralde <mauricio.iturralde@irit.fr, mauro@miturralde.com>


# Single Cell With Interference

FILE="Sim_scenario"   #OUTPUT FILE NAME
NUMSIM=5  #Nombre de simulations combien de simulations allez-vous faire pour chaque scanario et chaque algorithme, dans ce cas 5
FILENAME="video_be_voip"   # une simulation de flux vidéo, flux best effort et flux voip, appelez-le 'video_be_voip'.
COUNT=1      #// ne touchez pas à ça!
CELS=1       # NUMBER OF CELLS // ne touchez pas à ça!
TOTALNAME="" #// ne touchez pas à ça!
MINUSERS=3 # Start users
INTERVAL=3 # Interval between users
MAXUSERS=18 # max of users 

# params of LTE-SIM MULTICEL

RADIUS=1.5 # Radius in Km
NBUE=0 #Number of UE's # Nombre d'UE // ne touchez pas à ça!
NBVOIP=1  # Number of Voip Flows
NBVIDEO=1 #Number of Video
NBBE=1 # Number of Best Effort Flows
NBCBR=0 #Number of CBR flows
#Scheduler Type PF=1, MLWDF=2 EXP= 3 // ceci est réglé automatiquement dans cette rutine.
FRAME_STRUCT=1  # FDD or TDD 
SPEED=30 #User speed Vitesse de l'utilisateur
MAXDELAY=0.1 #100 ms (LaContraintes QoS )
VIDEOBITRATE=128 # 128 kbps 

NBUE=$MINUSERS
until [ $NBUE -gt $MAXUSERS ]; do

	# bash until loop
	until [ $COUNT -gt $NUMSIM ]; do
	TOTALNAME=$FILE"_"$COUNT"_"$FILENAME"_PF_"$NBUE"U"$CELS"C"".sim"
	../../ltesim SingleCellWithI $CELS $RADIUS $NBUE $NBVOIP $NBVIDEO $NBBE $NBCBR 1 $FRAME_STRUCT $SPEED $MAXDELAY $VIDEOBITRATE $COUNT > $TOTALNAME
        	echo FILE $TOTALNAME CREATED!

 	let COUNT=COUNT+1
	done
	COUNT=1

	until [ $COUNT -gt $NUMSIM ]; do
       	TOTALNAME=$FILE"_"$COUNT"_"$FILENAME"_MLWDF_"$NBUE"U"$CELS"C"".sim"
	../../ltesim SingleCellWithI $CELS $RADIUS $NBUE $NBVOIP $NBVIDEO $NBBE $NBCBR 2 $FRAME_STRUCT $SPEED $MAXDELAY $VIDEOBITRATE $COUNT > $TOTALNAME
       	echo FILE $TOTALNAME CREATED!
	 let COUNT=COUNT+1
	done
	COUNT=1

	until [ $COUNT -gt $NUMSIM ]; do
  	      TOTALNAME=$FILE"_"$COUNT"_"$FILENAME"_EXPPF_"$NBUE"U"$CELS"C"".sim"
	../../ltesim SingleCellWithI $CELS $RADIUS $NBUE $NBVOIP $NBVIDEO $NBBE $NBCBR 3 $FRAME_STRUCT $SPEED $MAXDELAY $VIDEOBITRATE $COUNT > $TOTALNAME
   	    echo FILE $TOTALNAME CREATED!
 	let COUNT=COUNT+1
	done
	COUNT=1
let NBUE=NBUE+INTERVAL
done
echo SIMULATION FINISHED!
echo CREATING RESULTS REPORT!

# params 1 MINUSERS, 2 MAXUSERS, 3 INTERVAL, 4 FILENAME, 5 FILE, 6 NUMSIM, 7 TypeFlow, Graphic_name

# result shells
./packet_loss_ratio.sh $MINUSERS $MAXUSERS $INTERVAL $FILENAME $FILE $NUMSIM VIDEO Packet-Loss-Ratio
./packet_loss_ratio.sh $MINUSERS $MAXUSERS $INTERVAL $FILENAME $FILE $NUMSIM VOIP Packet-Loss-Ratio
./packet_loss_ratio.sh $MINUSERS $MAXUSERS $INTERVAL $FILENAME $FILE $NUMSIM INF_BUF Packet-Loss-Ratio
./thoughput_comp.sh $MINUSERS $MAXUSERS $INTERVAL $FILENAME $FILE $NUMSIM VIDEO Throughput
./thoughput_comp.sh $MINUSERS $MAXUSERS $INTERVAL $FILENAME $FILE $NUMSIM VOIP Throughput
./thoughput_comp.sh $MINUSERS $MAXUSERS $INTERVAL $FILENAME $FILE $NUMSIM INF_BUF Throughput
./delay_comp.sh $MINUSERS $MAXUSERS $INTERVAL $FILENAME $FILE $NUMSIM VIDEO Delay
./delay_comp.sh $MINUSERS $MAXUSERS $INTERVAL $FILENAME $FILE $NUMSIM VOIP Delay
./delay_comp.sh $MINUSERS $MAXUSERS $INTERVAL $FILENAME $FILE $NUMSIM INF_BUF Delay
./spectral_efficiency_comp.sh $MINUSERS $MAXUSERS $INTERVAL $FILENAME $FILE $NUMSIM Spectral-Efficiency Spec-Eff
./fairnessIndex_comp.sh $MINUSERS $MAXUSERS $INTERVAL $FILENAME $FILE $NUMSIM  VIDEO Fairness-Index
./fairnessIndex_comp.sh $MINUSERS $MAXUSERS $INTERVAL $FILENAME $FILE $NUMSIM  VOIP Fairness-Index
./fairnessIndex_comp.sh $MINUSERS $MAXUSERS $INTERVAL $FILENAME $FILE $NUMSIM  INF_BUF Fairness-Index


 


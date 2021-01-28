# Multiplication Game


## Concept
Learning multiplication is not a simple task. It often involves sitting down with pen and paper and repeating the same equations over and over again. In the age of decreasing attention span, it can be difficult to get kids to sit at a table for hours and repeat the same task for hours. 

This project aims to tackle that by developing an easier way of learning and getting better at multiplication.  

My main goal was to remove as many obstructions between the state of not studying and studying. There is no need for pen and paper, there is no need for somebody to check the student's work, there is no need for somebody to pick which multiplications the student should solve. And there is no need to sit at a desk and practice for half an hour at a time. 

I wanted to implement a system where the student will want to practice more times per day in short bursts. Most people are only capable of 5 - 10 minutes of effective learning at a time. Trying to do more than that is possible, but it is most often futile.
 
 
 ## Setting up 
 
Initialize game data by running reset_spiffs() function. 

Enable more multiplications by editing the "enabled" array in game_logic.cpp file.

Game data is stored in SPIFFS as gamedata.conf. Statistical data is stored every 100 solved equations in the stat.conf file. More work is yet to be done to be able to retrieve the data in json or csv form.

![Vezje za igro](/Circuit_bb.png)






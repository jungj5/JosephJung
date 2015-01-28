mondaydistance=9
mondaytime=4532
mondaytime2=75
mondaytime3=.383

tuesdaydistance=5
tuesdaytime=2453
tuesdaytime2=40
tuesdaytime3=.166667

thursdaydistance=3.1
thursdaytime=1269
thursdaytime2=21
thursdaytime3=.816667
totaldistance=mondaydistance+tuesdaydistance+thursdaydistance
totaltimeminutes=(mondaytime+tuesdaytime+thursdaytime)/60
totaltimeseconds=.567*60


print "I ran a total of", totaldistance, "miles in", totaltimeminutes, "minutes and", totaltimeseconds, "seconds over the course of the week."

mondayaverage=(mondaytime2/mondaydistance)
mondayaverage2=mondaytime3*60
print "Average speed on Monday is", mondayaverage, "minutes and", mondayaverage2, "seconds per mile"

tuesdayaverage=(tuesdaytime2/tuesdaydistance)
tuesdayaverage2=tuesdaytime3*60
print "Average speed on Tuesday is", tuesdayaverage, "minutes and", tuesdayaverage2, "seconds per mile"

thursdayaverage=(thursdaytime2/thursdaydistance)
thursdayaverage2=thursdaytime3*60
print "Average speed on Thursday is", thursdayaverage, "minutes and", thursdayaverage2, "seconds per mile"

overalldistance=17.1
overalltime2=137
overalltime3=.033333
overallaverage=(overalltime2/overalldistance)
overallaverage2=overalltime3*60
print "Average overall speed is", overallaverage, "and", overallaverage2, "seconds per mile"
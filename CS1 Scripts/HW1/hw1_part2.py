ns06=62130
ns08=66310.
ns10=69160
ns12=72560.
rs06=93950
secondrs06=93950.
rs08=97970.
rs10=100660
secondrs10=100660.
rs12=102190.

ns0608=((ns08/ns06)-1)*100
print "Percent increase 2006 to 2008 for network and systems is", ns0608

ns0810=((ns10/ns08)-1)*100
print "Percent increase 2008 to 2010 for network and systems is", ns0810

ns1012=((ns12/ns10)-1)*100
print "Percent increase 2010 to 2012 for network and systems is", ns1012

rs0608=((rs08/rs06)-1)*100
print "Percent increase 2006 to 2008 for research scientists is", rs0608

rs0810=((rs10/rs08)-1)*100
print "Percent increase 2008 to 2010 for research scientists is", rs0810

rs1012=((rs12/rs10)-1)*100
print "Percent increase 2010 to 2012 for research scientists is", rs1012

ratio1=secondrs06/ns06
ratio2=rs08/ns08
ratio3=secondrs10/ns10
ratio4=rs12/ns12
print "Max ratio of salaries across four different years is", max(ratio1,ratio2,ratio3,ratio4)
print "Min ratio of salaries across four different years is", min(ratio1,ratio2,ratio3,ratio4)
import parse_url_new

url = raw_input("Please enter a url: ")
n = int(raw_input("Please enter a number: "))

all_links = [url]

all_links += parse_url_new.get_links(url)
unvisited = parse_url_new.get_links(url)

while len(all_links) <= n and len(unvisited) > 0:
    a = parse_url_new.get_links(unvisited.pop(0))
    temp = []
    for l in a:
        if l in all_links:
            pass
        else:
            temp.append(l)
    if len(all_links) + len(temp) > n:
        pass
    else:
        all_links = all_links + temp
        unvisited = unvisited + temp
        
count = 0
count2 = 0
for i in range(len(all_links)):
    if "nottingham" in all_links[i] or "Nottingham" in all_links[i]:
        count += 1
    if "london" in all_links[i] or "London" in all_links[i]:
        count2 += 1
    
        
    
dictionary = dict()
for link in all_links:
    a = link.split("/")
    date = a[4]
    if date in dictionary:
        dictionary[date] += 1
    else:
        dictionary[date] = 1
alist = dictionary.keys()
alist = sorted(alist)
blist = dictionary.values()
blist = max(blist)
def findblist(blist):
    for item in dictionary:
        if dictionary[item] == blist:
            print item





print "Part 1:"
print all_links
print
print "Part 2: Counting URLs containing substrings"
print "Number containing 'nottingham' is:",count 
print "Number contain 'london' is:",count2
print
print "Part 3, modification dates:"
print "Earliest date:",alist[0], "with", dictionary[alist[0]], "changes"
print "Latest date:",alist[-1], "with", dictionary[alist[-1]], "changes"
print "Most modifications is", blist, ",dates are:"
findblist(blist)
print







class HasseDiagram:                                                # class for relation finding

    setElements= set()                                          # some required variables
    relationNumber = int()
    relations = set()
    IFileName = str()
    OFileName = str()
    cursor = 0
    fileSize=0
    adding1 = set()
    adding2 = set()
    removing = set()

    def __init__(self, IfileName, OFileName):                               # constructor
        self.IFileName = IfileName
        self.OFileName = OFileName
        renewOFile = open(OFileName,'w')                                                        # make ready output file
        renewOFile.close()
        file = open("input.txt",'r')                                                            # reads file size to use it later
        file.read()
        self.fileSize=file.tell()

    def writeToFile(self,sentence):                                                       # this function takes a string as parameter and writes it to the output file
        file = open(self.OFileName, 'a')
        file.write(sentence)
        file.close()


    def takeInput(self):

        file = open("input.txt","r")                        # opens the input file in reading mode
        file.seek(self.cursor)

        firstLine = file.readline()
        if(self.cursor == self.fileSize-1):                 # if the cursor is on end of file
            return False                                    # then return False to finish program

        firstLine = firstLine[0:-1]

        if not firstLine.isnumeric():                       # checks if number of relation is true or not
            for x in firstLine:
                if(x != ' ' and x!= '\n'):
                    raise Exception("Sorry number of relation is expected. Number of relation not given or wrong format.  : {}".format(firstLine))

            for line in file.readlines():
                for x in line:
                    if(x != ' ' and x!= '\n'):
                        raise Exception("Sorry number of relation is expected. Number of relation not given or wrong format.  : {}".format(line))
            return False

        relationNumber = int(firstLine)                   # takes relation size from the file

        self.setElements.clear()                           # clearing the old elements and relations
        self.relations.clear()

        elements = file.readline()
        length = len(elements)-1
        for x in range (0,length):                     # fetching the set elements in a loop
            if( x%2 == 1 and elements[x] != ','):
                raise Exception("The given elements format is wrong:{} it should be like: a,b,c,d".format(elements))
                return False
            elif( x%2==0 and elements[x] == ',' ):
                raise Exception("The given elements format is wrong:{} it should be like: a,b,c,d".format(elements))
                return False
            elif(x%2==0):
                self.setElements.add(elements[x])           # if it has not any problem then adds it to the set


        for relation in range(relationNumber):                                              # fetching the relations
            r = file.readline()
            if(len(r) != 4):                                                                # some validation for relations
                raise Exception("Wrong Relation format :{}".format(r[0:-1]) )
            elif(r[1] != ','):
                raise Exception("Wrong Relation format {}".format(r[0:-1]) )
            elif( (not self.setElements.__contains__(r[0]) ) or  ( not self.setElements.__contains__(r[2]) )  ):
                raise Exception("Relation element {} or {} is not in set".format(r[0],r[2]))
            elif(self.setElements.__contains__(r[0]) and self.setElements.__contains__(r[2])):
                self.relations.add(r[0:3])
        # else:
                #throw if the relation elemnt not in set

        self.cursor = file.tell()                                       # holds the last cursor place to use it again
        file.close()
        return True


    def findPairsForReflexivity(self):
        relations = []
        flag = True
        for x in self.setElements:
            relations.append( x + ',' + x )
        return relations


    def findPairsForAntiSymmetric(self):
        relations = []
        for r in self.relations:
            if( self.relations.__contains__( r[::-1] ) and r[::-1]  != r ):
                if( not relations.__contains__(r[::-1]) ):
                    relations.append(r)
        return relations


    def findPairsForTransitivity(self):
        relations = set()
        for r in self.relations:
            if(r[0] != r[2]):                                                                    # we skip the relations that are like (a,a)
                transittedOnes = list( filter(lambda x : x[0] == r[2] and x[0] != x[2], self.relations) )         # We take the list of the relations that their second element is equals to first element of any relation
                for transitted in  transittedOnes:
                    transitiveElement = r[0] + ',' + transitted[2]
                    if(transitiveElement[0] != transitiveElement[2]):
                        relations.add(transitiveElement)
        return relations


    def convert_poset(self):


        self.adding2 = self.findPairsForReflexivity()                # making reflexive the poset
        for x in self.adding2:
            if(not self.relations.__contains__(x)):
                self.relations.add(x)

        removing = self.findPairsForAntiSymmetric()                   # making antysymmetric the poset
        for x in removing:
            self.relations.remove(x)

        self.adding1 = self.findPairsForTransitivity()               # making transitive the poset
        for x in self.adding1:
            if(not self.relations.__contains__(x)):
                hasseDiagram.relations.add(x)


    def remove_unneccesaries(self):
        for x in hasseDiagram.adding1:                                      # removing the unneccesary transitive relations
            if(hasseDiagram.relations.__contains__(x)):
                hasseDiagram.relations.remove(x)

        for x in hasseDiagram.setElements:                                  # removing the reflexive relations like (a,a)
            a = x+','+x
            if ( hasseDiagram.relations.__contains__(a) ):
                hasseDiagram.relations.remove(a)



# main part of the program
hasseDiagram = HasseDiagram("input.txt","output.txt")

while hasseDiagram.takeInput():                               # while takeInput function reading the file
  #  print(hasseDiagram.relations)

    hasseDiagram.convert_poset()

    hasseDiagram.writeToFile("n\nPOSET: ")
    i=0
    for x in hasseDiagram.relations :
        hasseDiagram.writeToFile('(' + x + ')')               # writes all relations to the output file one by one
        i = i+1
        if(i != len(hasseDiagram.relations)):                   # if the element is not the last element
            hasseDiagram.writeToFile(",")                           # then, writes ","

    hasseDiagram.remove_unneccesaries()

    hasseDiagram.writeToFile('\n')
    for x in hasseDiagram.relations:
        hasseDiagram.writeToFile(x+'\n')               # writes all last poset elements to the output file one by one

  #  print(hasseDiagram.relations)
  #  print()
print('The '+ hasseDiagram.OFileName +' file is made successfully...')

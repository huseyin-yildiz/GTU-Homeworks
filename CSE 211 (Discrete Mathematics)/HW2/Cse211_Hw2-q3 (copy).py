class RelationFinder:                                                # class for relation finding

    setElements= set()                                          # some required variables
    relationNumber = int()
    relations = []
    IFileName = str()
    OFileName = str()
    cursor = 0
    fileSize=0

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
            if(len(r) != 4):                                                                # some validation foe relations
                raise Exception("Wrong Relation format :{}".format(r[0:-1]) )
            elif(r[1] != ','):
                raise Exception("Wrong Relation format {}".format(r[0:-1]) )
            elif( (not self.setElements.__contains__(r[0]) ) or  ( not self.setElements.__contains__(r[2]) )  ):
                raise Exception("Relation element {} or {} is not in set".format(r[0],r[2]))
            elif(self.setElements.__contains__(r[0]) and self.setElements.__contains__(r[2])):
                self.relations.append(r[0:3])
        # else:
                #throw if the relation elemnt not in set

        self.cursor = file.tell()                                       # holds the last cursor place to use it again
        file.close()
        return True




    def checkReflexivity(self):                                             # This function checks Reflexivity propert
        relation = str()
        flag = True
        for x in self.setElements:
            relation = x + ',' + x
            if(not self.relations.__contains__(relation)):                                  # if relations has not the relation that must be in relations
                self.writeToFile("Reflexive: No, (,{},{},)is not found.\n".format(x,x))         # then writes to the file No
                flag = False
                break
        if(flag):                                                                           # if there is no any problem
            self.writeToFile("Reflexive: Yes, all elements are present. ({}) is found.\n".format(relation))         # then it writes to the file yes



    def checkSymmetric(self):                                                                       # this function checks symmetric property
        for r in self.relations:
            if( not self.relations.__contains__( r[::-1] ) ):                                       # if is there any relation which has not symmetric of its own
                self.writeToFile("Symmetric: No, ({}) is found whereas ({}) is not found.\n".format(r,r[::-1]))  #then we gives output as not found and finish the function with return keyword
                return
        self.writeToFile("Symmetric: Yes, all relations have symmetic in the given set. ({}) and ({}) also found.\n".format(self.relations[2],self.relations[2][::-1]))                                 # if all relations have their symmetrics in the relation set
                                                                                                    # we gives output as all relations have symmetrics



    def checkAntiSymmetric(self):
          flag = True
          for r in self.relations:
            if( self.relations.__contains__( r[::-1] ) and r[::-1]  != r ):                                 # checks if an relation has its symmetrics
                self.writeToFile("Antisymmetric: No, ({}) is found and ({}) also is found.\n".format(r,r[::-1]) )                 # then writes No for antysmmetric property
                flag = False
                break
          if(flag):
            self.writeToFile("Antisymmetric: Yes, ({}) is found whereas ({}) is not found.\n".format(self.relations[1],self.relations[1][::-1]))




    def checkTransitive(self):                                                                   # this function checks Transitive property
        transtv = str()
        transtd = str()
        reltion = str()
        flag = True                                                                                 # for holding if its transitive or not
        for r in self.relations:
            if(r[0] != r[2] and flag):                                                                    # we skip the relations that are like (a,a)
                transittedOnes = list( filter(lambda x : x[0] == r[2] and x[0] != x[2], self.relations) )         # We take the list of the relations that their second element is equals to first element of any relation
                for transitted in  transittedOnes:
                    transitiveElement = r[0] + ',' + transitted[2]
                    if( not self.relations.__contains__(transitiveElement) ):
                        flag = False
                        self.writeToFile("Transitive: No, ({}) is not found but ({}) and ({}) are found.\n".format(transitiveElement,r,transitted))
                    if(transittedOnes[ len(transittedOnes)-1 ] == transitted ):                 # last example that prove are holded to use later
                        transtd = transitted
                        transtv = transitiveElement
                        reltion = r
            if( self.relations[ len(self.relations)-1 ] == r and flag  ):
                self.writeToFile("Transitive: Yes, ({}) is found since ({}) and ({}) are found.\n".format(transtv,reltion,transtd))



# main part of the program
relationfinder= RelationFinder("input.txt","output.txt")

while relationfinder.takeInput():                               # while takeInput function reading the file
    relationfinder.writeToFile("n\n")
    for x in relationfinder.relations:
        relationfinder.writeToFile('(' + x + ')')               # writes all relations to the output file one by one
    relationfinder.writeToFile('\n')

    relationfinder.checkReflexivity()                           # checks all properties one by one
    relationfinder.checkSymmetric()
    relationfinder.checkAntiSymmetric()
    relationfinder.checkTransitive()

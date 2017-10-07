def maxedOut(inputString):
    for char in inputString:
        if char != 'z':
            return False
    return True
    
def incrementChar(inputChar):
    alphaChars = ['A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z']
    inputIndex = findIndex(inputChar, alphaChars)
    outputIndex = inputIndex + 1
    if outputIndex == 52:
        outputIndex = 0
    return alphaChars[outputIndex]
    
def findIndex(inputElement, inputArray):
    index = 0
    for element in inputArray:
        if element == inputElement:
            return index
        index += 1
    return len(inputArray) + 1
    
def incrementString(inputString):
    length = len(inputString)
    if inputString[-1] != 'z':
        return inputString[:-1] + incrementChar(inputString[-1])
    else:
        outputString = incrementString(inputString[:-1]) + incrementChar(inputString[-1])
        return outputString
    
if __name__ == "__main__":
    sampleString = input("Enter a 4-character string: ")
    for _ in range(456976):
        sampleString = incrementString(sampleString)
        print(sampleString)
    
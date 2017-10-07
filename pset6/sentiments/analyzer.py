import nltk

class Analyzer():
    """Implements sentiment analysis."""

    def __init__(self, positives, negatives):
        """Initialize Analyzer."""
        self.positives = []
        self.negatives = []
        with open(positives, 'r') as input_file:
            for line in input_file:
                if line.startswith(';'):
                    continue
                else:
                    self.positives.append(line.strip())
        with open(negatives, 'r') as input_file:
            for line in input_file:
                if line.startswith(';'):
                    continue
                else:
                    self.negatives.append(line.strip())

    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""
        self.score = 0
        for word in text.split():
            if word in self.positives:
                self.score += 1
            elif word in self.negatives:
                self.score -= 1
        return self.score

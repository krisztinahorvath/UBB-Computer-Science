class ValidationError(Exception):
    pass


class Validations:
    def __init__(self, sentence, sentence_list):
        self.sentence = sentence.strip()
        self.sentence_list = sentence_list

    def duplicate_sentence(self):
        if self.sentence in self.sentence_list:
            raise ValidationError("\tInvalid input! The sentence that you are trying to add already exists!")

    def valid_sentence(self):
        try:
            self.duplicate_sentence()
            if len(self.sentence) < 3:
                raise ValidationError("\tInvalid input! "
                                      "The sentence must contain at least one word of at least three letters!")
            for word in self.sentence.split(" "):
                if len(word) < 3:
                    raise ValidationError("\tInvalid input! Not all words have three letters!")
        except ValidationError as ve:
            raise ve




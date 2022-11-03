from src.ui.ui import UI
from src.start.settings import repository, students, disciplines, grades


ui = UI(repository, students, disciplines, grades)
ui.start()

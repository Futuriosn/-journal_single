from writer import *
from reader import *
from page_size import *


#
def create_writer(home: str,
                  name: str,
                  ps: page_size = page_size.Small,
                  dest_id: int = 0,
                  lazy: bool = False) -> writer: pass


def create_reader(lazy: bool = False) -> reader: pass


def reader_join(rd: reader,
                home: str,
                name: str,
                from_time: int,
                ps: page_size = page_size.Small,
                dest_id: int = 0
                ): pass

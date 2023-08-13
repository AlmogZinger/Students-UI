from pathlib import Path

from qtgqlcodegen.config import QtGqlConfig


config = QtGqlConfig(graphql_dir=Path(__file__).parent, env_name='Students')

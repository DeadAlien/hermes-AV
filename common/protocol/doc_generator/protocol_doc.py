"""
Protocol Documentation Generator

Input:
protocol_config.json

Output:
out/
Protocol_Specification.docx
protocol_summary.json
"""

from pathlib import Path
import json

CONFIG_FILE = "protocol_config.json"
OUTPUT_DIR = "out"

def load_config():
    with open(CONFIG_FILE, "r") as f:
        return json.load(f)

def generate_document(config):
    """
    Future:
    - Generate DOCX
    - Generate PNG diagrams
    - Generate PDF
    """

    print("=" * 60)
    print("Module :", config["module_name"])
    print("Version:", config["module_version"])
    print("=" * 60)

    print("Purpose:")
    print(config["purpose"])

    print("\nMessage Types:")
    for msg in config["message_types"]:
        print(
            f'{msg["id"]} | {msg["name"]} | {msg["direction"]}'
        )

def main():

    Path(OUTPUT_DIR).mkdir(exist_ok=True)

    config = load_config()
    generate_document(config)


if __name__ == "__main__":
    main()

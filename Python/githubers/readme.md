# Building Github graph

The project is aimed at building graph of GitHub users. The code is written in Python 3.

At the moment there are two scripts, that are contained id `/src` folder.

* `main.py` – scripts must be launched with two following arguments: GitHub login and password of registered user. For example:

```bash
python3 main.py Vasya crocodile3
```
`main.py` downloads `<id>.json` files where `<id>` is a GitHub user identifier. During launch, the script scans the `path` for already downloaded jsons, finds maximal downloaded id and starts requesting for greater ones, so the program can be stopped and continued at any time.

* `githubers.py` – utilities, which `main.py` is using.

* `config.py` – module loads configuration file and sets parameters according to `/resourses/config.json` file. Relative `path`, where loaded jsons are stored, is contained here.

## To launch the program...

...you need to launch `main.py`

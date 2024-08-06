-- Added most common usages to avoid misinterpreting names like "Defeat."
SELECT name FROM songs WHERE name LIKE '% feat. %' OR name LIKE '%(feat.%' OR name LIKE '%[feat.%';

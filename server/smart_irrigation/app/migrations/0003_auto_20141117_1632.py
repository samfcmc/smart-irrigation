# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models, migrations


class Migration(migrations.Migration):

    dependencies = [
        ('app', '0002_auto_20141117_1530'),
    ]

    operations = [
        migrations.RenameField(
            model_name='userplants',
            old_name='plant',
            new_name='plants',
        ),
    ]
